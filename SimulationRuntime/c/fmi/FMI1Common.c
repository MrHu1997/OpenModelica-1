/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE
 * OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "FMI1Common.h"

/*
 * Used for logging import messages.
 */
void importlogger(jm_callbacks* c, jm_string module, jm_log_level_enu_t log_level, jm_string message)
{
  printf("module = %s, log level = %s: %s\n", module, jm_log_level_to_string(log_level), message);
}

/*
 * Used for logging FMU messages.
 * Logger function used by the FMU internally.
 */
void fmi1logger(fmi1_component_t c, fmi1_string_t instanceName, fmi1_status_t status, fmi1_string_t category, fmi1_string_t message, ...)
{
  va_list argp;
  va_start(argp, message);
  fmi1_log_forwarding_v(c, instanceName, status, category, message, argp);
  va_end(argp);
}

/*
 * OpenModelica uses signed integers and according to FMI specifications the value references should be unsigned integers.
 * So to overcome this we use value references as Real in the Modelica code.
 * This function converts back the value references from double to int and use them in FMI specific functions.
 */
fmi1_value_reference_t* real_to_fmi1_value_reference(int numberOfValueReferences, double* valuesReferences)
{
  fmi1_value_reference_t* valuesReferences_int = malloc(sizeof(fmi1_value_reference_t)*numberOfValueReferences);
  int i;
  for (i = 0 ; i < numberOfValueReferences ; i++)
    valuesReferences_int[i] = (int)valuesReferences[i];
  return valuesReferences_int;
}

/*
 * Wrapper for the FMI function fmiGetReal.
 * parameter flowStatesInput is dummy and is only used to run the equations in sequence.
 * Returns realValues.
 */
void fmi1GetReal_OMC(void* in_fmi1me, int numberOfValueReferences, double* realValuesReferences, double flowStatesInput, double* realValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, realValuesReferences);
  fmi1_import_get_real(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_real_t*)realValues);
  free(valuesReferences_int);
}

/*
 * Wrapper for the FMI function fmiSetReal.
 * Returns status.
 */
double fmi1SetReal_OMC(void* in_fmi1me, int numberOfValueReferences, double* realValuesReferences, double* realValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, realValuesReferences);
  fmi1_status_t fmistatus = fmi1_import_set_real(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_real_t*)realValues);
  return (double)fmistatus;
}

/*
 * Wrapper for the FMI function fmiGetInteger.
 * parameter flowStatesInput is dummy and is only used to run the equations in sequence.
 * Returns integerValues.
 */
void fmi1GetInteger_OMC(void* in_fmi1me, int numberOfValueReferences, double* integerValuesReferences, double flowStatesInput, int* integerValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, integerValuesReferences);
  fmi1_import_get_integer(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_integer_t*)integerValues);
  free(valuesReferences_int);
}

/*
 * Wrapper for the FMI function fmiSetInteger.
 * Returns status.
 */
double fmi1SetInteger_OMC(void* in_fmi1me, int numberOfValueReferences, double* integerValuesReferences, int* integerValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, integerValuesReferences);
  fmi1_status_t fmistatus = fmi1_import_set_integer(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_integer_t*)integerValues);
  return (double)fmistatus;
}

/*
 * Wrapper for the FMI function fmiGetBoolean.
 * parameter flowStatesInput is dummy and is only used to run the equations in sequence.
 * Returns booleanValues.
 */
void fmi1GetBoolean_OMC(void* in_fmi1me, int numberOfValueReferences, double* booleanValuesReferences, double flowStatesInput, int* booleanValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, booleanValuesReferences);
  fmi1_import_get_boolean(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_boolean_t*)booleanValues);
  free(valuesReferences_int);
}

/*
 * Wrapper for the FMI function fmiSetBoolean.
 * Returns status.
 */
double fmi1SetBoolean_OMC(void* in_fmi1me, int numberOfValueReferences, double* booleanValuesReferences, int* booleanValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, booleanValuesReferences);
  fmi1_status_t fmistatus = fmi1_import_set_boolean(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_boolean_t*)booleanValues);
  return (double)fmistatus;
}

/*
 * Wrapper for the FMI function fmiGetString.
 * parameter flowStatesInput is dummy and is only used to run the equations in sequence.
 * Returns stringValues.
 */
void fmi1GetString_OMC(void* in_fmi1me, int numberOfValueReferences, double* stringValuesReferences, double flowStatesInput, char** stringValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, stringValuesReferences);
  fmi1_import_get_string(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_string_t*)stringValues);
  free(valuesReferences_int);
}

/*
 * Wrapper for the FMI function fmiSetString.
 * Returns status.
 */
double fmi1SetString_OMC(void* in_fmi1me, int numberOfValueReferences, double* stringValuesReferences, char** stringValues)
{
  FMI1ModelExchange* FMI1ME = (FMI1ModelExchange*)in_fmi1me;
  fmi1_value_reference_t* valuesReferences_int = real_to_fmi1_value_reference(numberOfValueReferences, stringValuesReferences);
  fmi1_status_t fmistatus = fmi1_import_set_string(FMI1ME->FMIImportInstance, valuesReferences_int, numberOfValueReferences, (fmi1_string_t*)stringValues);
  return (double)fmistatus;
}

#ifdef __cplusplus
}
#endif
