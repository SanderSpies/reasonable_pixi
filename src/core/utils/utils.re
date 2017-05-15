/* let createIndicesForQuads size => {
  let totalIndices = size * 6;
  let indices = array Tgls.Gl.short;
  let acc pos answer => {

  };
}; */

let nextUid = ref 0;
let uid () => {
  nextUid := !nextUid + 1;
  !nextUid
};

let hex2rgb hex => {
  [|
    float_of_int (((hex lsr 16) land 0xFF)) /. 255.,
    float_of_int (((hex lsr 8) land 0xFF)) /. 255.,
    float_of_int ((hex land 0xFF)) /. 255.
  |]
};


let hex2string () => {
  failwith "not implemented"
};

let rgb2hex () => {
  failwith "not implemented"
};

let getResolutionOfUrl url defaultValue => {
  failwith "not implemented"
};

let decomposeDataUri dataUri => {
  failwith "not implemented"
};

let getUrlFileExtension url => {
  failwith "not implemented"
};

let getSvgSize svgString => {
  failwith "not implemented"
};

let sign number => {
  if (number === 0) {
    0
  }
  else if (number < 0) {
    -1
  }
  else {
    1
  }
};

let destroyTextureCache () => {

};

let clearTextureCache () => {

};
