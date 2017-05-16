open Matrix;

let ux = [|1., 1., 0., -1., -1., -1., 0., 1., 1., 1., 0., -1., -1., -1., 0., 1.|];
let uy = [|0., 1., 1., 1., 0., -1., -1., -1., 0., 1., 1., 1., 0., -1., -1., -1.|];
let vx = [|0., -1., -1., -1., 0., 1., 1., 1., 0., 1., 1., 1., 0., -1., -1., -1.|];
let vy = [|1., 1., 0., -1., -1., -1., 0., 1., -1., -1., 0., 1., 1., 1., 0., -1.|];
let tempMatrices = ref [||];

let mul = ref [||];

let signum x => {
  if (x < 0.) {
    -1.
  }
  else if (x > 0.) {
    1.
  } else {
    0.
  }
};

let init () => {
  for i in 0 to 16 {
    let row = ref [||];

    for j in 0 to 16 {
      let _ux = signum((ux.(i) *. ux.(j)) +. (vx.(i) *. uy.(j)));
      let _uy = signum((uy.(i) *. ux.(j)) +. (vy.(i) *. uy.(j)));
      let _vx = signum((ux.(i) *. vx.(j)) +. (vx.(i) *. vy.(j)));
      let _vy = signum((uy.(i) *. vx.(j)) +. (vy.(i) *. vy.(j)));
      let break = ref false;
      for k in 0 to 16 {
        if (ux.(k) == _ux && uy.(k) == _uy && vx.(k) == _vx && vx.(k) == _vy && !break == false) {
          row := Array.append (!row) [|(float_of_int k)|];
          break := true;
          ()
        }
      }
    };
    mul := Array.append (!mul) ([|!row|]);
  };

  for i in 0 to 16 {
    let matrix = new matrix a::ux.(i) b::uy.(i) c::vx.(i) d::vy.(i) tx::0. ty::0. ();
    tempMatrices := Array.append (!tempMatrices) ([|matrix|]);
  }
};

init;

type direction =
  | East
  | South_east
  | South
  | South_west
  | West
  | North_west
  | North
  | North_east;

type mirror =
  | Mirror_vertical
  | Mirror_horizontal;

module GroupDB = {
  let uX ind => ux.(ind);
  let uY ind => uy.(ind);
  let vX ind => vx.(ind);
  let vY ind => vy.(ind);
  let inv rotation => {
    if ((rotation land 8) > 0) {
      rotation land 15
    }
    else {
      (-rotation) land 7
    }
  };
  let add rotationSecond rotationFirst => {
    (!mul).(rotationSecond).(rotationFirst)
  };
  let sub rotationSecond rotationFirst => {
    (!mul).(rotationSecond).(inv rotationFirst)
  };
  let rotate180 rotation => {
    rotation lxor 4
  };
  let isSwapWidthHeight rotation => {
    (rotation land 3) == 2
  };
  let byDirection dx dy => {
    if ((abs_float dx) *. 2. <= (abs_float dy)){
      if (dy >= 0.) {
        South
      }
      else {
        North
      }
    }
    else if ((abs_float dy) *. 2. <= (abs_float dx)) {
      if (dx >= 0.) {
        East
      }
      else {
        West
      }
    } else if (dy > 0.) {
      if (dx > 0.) {
        South_east
      }
      else {
        South_west
      }
    }
    else if (dx > 0.) {
      North_east
    }
    else {
      North_west
    }
  };
  let matrixAppendRotationInv matrix rotation ::tx=0. ::ty=0. => {
    let mat = (!tempMatrices).(inv rotation);
    mat#setTx tx;
    mat#setTy ty;
    matrix#append mat;
  };
};
