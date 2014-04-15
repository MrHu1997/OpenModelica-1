/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF THE BSD NEW LICENSE OR THE
 * GPL VERSION 3 LICENSE OR THE OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the OSMC (Open Source Modelica Consortium)
 * Public License (OSMC-PL) are obtained from OSMC, either from the above
 * address, from the URLs: http://www.openmodelica.org or
 * http://www.ida.liu.se/projects/OpenModelica, and in the OpenModelica
 * distribution. GNU version 3 is obtained from:
 * http://www.gnu.org/copyleft/gpl.html. The New BSD License is obtained from:
 * http://www.opensource.org/licenses/BSD-3-Clause.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, EXCEPT AS
 * EXPRESSLY SET FORTH IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE
 * CONDITIONS OF OSMC-PL.
 *
 */

/*! \file linearSolverLis.c
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "simulation_data.h"
#include "omc_error.h"
#include "varinfo.h"
#include "model_help.h"

#include "linearSystem.h"
#include "linearSolverLis.h"

/*! \fn allocate memory for linear system solver Lis 
 *
 */
int
allocateLisData(int n_row, int n_col, int nz, void** voiddata)
{
  DATA_LIS* data = (DATA_LIS*) malloc(sizeof(DATA_LIS));
  assertStreamPrint(NULL, 0 != data, "Could not allocate data for linear solver Lis.");

  data->n_col = n_col;
  data->n_row = n_row;
  data->nnz = nz;

  lis_vector_create(0, &(data->b));
  lis_vector_set_size(data->b, data->n_row, 0);

  lis_vector_create(0, &(data->x));
  lis_vector_set_size(data->b, data->n_row, 0);

  lis_solver_create(&(data->solver));
  lis_solver_set_option("-i fgmres ",data->solver);

  *voiddata = (void*)data;
  return 0;
}

/*! \fn free memory for linear system solver Lis 
 *
 */
int 
freeLisData(void **voiddata)
{
  DATA_LIS* data = (DATA_LIS*) *voiddata;
  
  lis_solver_destroy(data->solver);
  lis_vector_destroy(data->b);
  lis_vector_destroy(data->x);

  return 0;
}

/*! \fn solve linear system with Lis method
 *
 *  \param  [in]  [data]
 *                [sysNumber] index of the corresponing non-linear system
 *
 *  \author swagner
 */
int
solveLis(DATA *data, int sysNumber)
{
  int i, ret, success = 1;
  LINEAR_SYSTEM_DATA* systemData = &(data->simulationInfo.linearSystemData[sysNumber]);
  DATA_LIS* sData = (DATA_LIS*)systemData->solverData;

  /* Destroy the old matrix, create a new one and fill it with values */
  lis_matrix_destroy(sData->A);
  lis_matrix_create(0, &(sData->A));
  lis_matrix_set_size(sData->A, sData->n_row, 0);
  systemData->setA(data, systemData);
  lis_matrix_set_type(sData->A, LIS_MATRIX_CSR);
  lis_matrix_assemble(sData->A);

  /* fill b with values */
  systemData->setb(data, systemData);
  for(i=0; i<sData->n_row; i++)
  {
    lis_vector_set_value(LIS_INS_VALUE, i, systemData->b[i], sData->b);
  }

  /* solve */
  ret = lis_solve(sData->A,sData->b,sData->x,sData->solver);

  /* handle return status */
  switch(ret){
    case LIS_SUCCESS:
      success = 1;
      break;
    case LIS_ILL_OPTION:
    case LIS_BREAKDOWN:
    case LIS_OUT_OF_MEMORY:
    case LIS_MAXITER:
    case LIS_ERR_NOT_IMPLEMENTED:
    case LIS_ERR_FILE_IO:
    default:
      success = 0;
      break;
  }

  /* write solution */
  lis_vector_get_values(sData->x, 0, sData->n_col, systemData->x);

  lis_matrix_destroy(sData->A);

  return success;
}
