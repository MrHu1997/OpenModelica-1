// name: const7.mo
// keywords:
// status: correct
// cflags:   +d=scodeInst
//
// Correct, but old instantiation fails.
//


model M
  parameter Real A[1, n];
  parameter Integer n = size(A, 1);
end M;

// Result:
// class M
//   parameter Real A[1,1];
//   parameter Integer n = 1;
// end M;
// endResult
