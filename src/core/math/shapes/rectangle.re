class rectangle ::x=0. ::y=0. ::width=0. ::height=0. () => {
  val mutable _x:float = x;
  val mutable _y:float = y;
  val mutable _width:float = width;
  val mutable _height:float = height;

  pub getLeft => {
    _x;
  };

  pub getRight => {
    _x +. _width;
  };

  pub getTop => {
    _y;
  };

  pub getBottom => {
    _y +. _height;
  };

  pub getWidth => {
    _width;
  };

  pub getHeight => {
    _height;
  };

  pub clone => {
    new rectangle x::_x y::_x width::_width height::_height ();
  };

  pub copy (rectangle:rectangle) => {
    _x = rectangle#getLeft;
    _y = rectangle#getTop;
    _width = rectangle#getWidth;
    _height = rectangle#getHeight;

    this
  };

  pub contains x y => {
    if (_width <= 0. || _height <= 0.) {
      false
    }
    else if ((x >= _x && x < (_x +. _width)) && (y > _y && y < (_y +. height))) {
      true
    }
    else {
      false
    }
  };

  pub pad ::paddingX=? ::paddingY=? => {
    let paddingX = switch paddingX {
      | Some paddingX => paddingX
      | None => 0.
    };
    let paddingY = switch paddingY {
      | Some paddingY => paddingY
      | None => 0.
    };

    _x = _x -. paddingX;
    _y = _y -. paddingY;

    _width = _width +. paddingX *. 2.;
    _height = _height +. paddingY *. 2.;
  };

  pub fit (rectangle:rectangle) => {
    if _x < rectangle#getX
  };

  pub enlarge => {

  };

};

let empty () => {
  new rectangle ();
};
