// name: BuiltinTime
// keywords:
// status: correct
// cflags:   +d=scodeInst
//
// Checks that the builtin variable time is handled.
//

model BuiltinTime
  Real x = time;
end BuiltinTime;

// Result:
// class BuiltinTime
//   Real x = time;
// end BuiltinTime;
// endResult
