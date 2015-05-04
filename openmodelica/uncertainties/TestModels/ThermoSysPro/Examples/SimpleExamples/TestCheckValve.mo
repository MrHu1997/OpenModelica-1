within ThermoSysPro.Examples.SimpleExamples;
model TestCheckValve
  annotation(Diagram);
  ThermoSysPro.WaterSteam.BoundaryConditions.SourceP sourceP annotation(Placement(transformation(x=-94.0, y=30.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.BoundaryConditions.SinkP puitsP(P0=600000.0) annotation(Placement(transformation(x=94.0, y=30.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.Machines.StaticCentrifugalPump staticCentrifugalPump1 annotation(Placement(transformation(x=-20.0, y=70.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.Machines.StaticCentrifugalPump staticCentrifugalPump2 annotation(Placement(transformation(x=-20.0, y=-10.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.Volumes.VolumeD volumeD annotation(Placement(transformation(x=-40.0, y=30.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.PressureLosses.CheckValve checkValve1 annotation(Placement(transformation(x=20.0, y=70.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.PressureLosses.CheckValve checkValve2 annotation(Placement(transformation(x=18.0, y=-10.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.Volumes.VolumeC volumeC annotation(Placement(transformation(x=40.0, y=30.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.PressureLosses.LumpedStraightPipe perteDP annotation(Placement(transformation(x=-70.0, y=30.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.PressureLosses.LumpedStraightPipe perteDP1 annotation(Placement(transformation(x=70.0, y=30.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.BoundaryConditions.SourceP sourceP1 annotation(Placement(transformation(x=-50.0, y=-70.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.BoundaryConditions.SinkP puitsP1(P0=600000.0) annotation(Placement(transformation(x=30.0, y=-70.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.InstrumentationAndControl.Blocks.Sources.Pulse pulse(amplitude=600000.0, width=50, period=100, offset=300000.0) annotation(Placement(transformation(x=-90.0, y=-70.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
  ThermoSysPro.WaterSteam.PressureLosses.CheckValve checkValve3 annotation(Placement(transformation(x=-10.0, y=-70.0, scale=0.1, aspectRatio=1.0, flipHorizontal=false, flipVertical=false)));
equation
  connect(volumeD.Cs1,staticCentrifugalPump1.C1) annotation(Line(points={{-40,40},{-40,70},{-30,70}}, color={0,0,255}));
  connect(volumeD.Cs2,staticCentrifugalPump2.C1) annotation(Line(points={{-40,20.2},{-40,-10},{-30,-10}}, color={0,0,255}));
  connect(staticCentrifugalPump1.C2,checkValve1.C1) annotation(Line(points={{-10,70},{-2,70},{-2,70},{9,70}}, color={0,0,255}));
  connect(checkValve1.C2,volumeC.Ce2) annotation(Line(points={{31,70},{40,70},{40,39}}, color={0,0,255}));
  connect(checkValve2.C2,volumeC.Ce3) annotation(Line(points={{29,-10},{40,-10},{40,20}}, color={0,0,255}));
  connect(staticCentrifugalPump2.C2,checkValve2.C1) annotation(Line(points={{-10,-10},{0,-10},{0,-10},{7,-10}}, color={0,0,255}));
  connect(perteDP.C2,volumeD.Ce) annotation(Line(points={{-60,30},{-50,30}}, color={0,0,255}));
  connect(volumeC.Cs,perteDP1.C1) annotation(Line(points={{50,30},{60,30}}, color={0,0,255}));
  connect(perteDP1.C2,puitsP.C) annotation(Line(points={{80,30},{84,30}}, color={0,0,255}));
  connect(sourceP.C,perteDP.C1) annotation(Line(points={{-84,30},{-80,30}}, color={0,0,255}));
  connect(sourceP1.C,checkValve3.C1) annotation(Line(points={{-40,-70},{-21,-70}}, color={0,0,255}));
  connect(checkValve3.C2,puitsP1.C) annotation(Line(points={{1,-70},{20,-70}}, color={0,0,255}));
  connect(pulse.y,sourceP1.IPressure) annotation(Line(points={{-79,-70},{-55,-70}}, color={0,0,255}));
end TestCheckValve;
