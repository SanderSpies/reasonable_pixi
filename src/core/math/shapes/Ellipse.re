open Rectangle;

class ellipse ::x=0. ::y=0. ::width=0. ::height=0. () => {
  val mutable _x:float = x;
  val mutable _y:float = y;
  val mutable _width:float = width;
  val mutable _height:float = height;

  pub clone => {
    new ellipse x::_x y::_y width::_width height::_height ();
  };

  pub contains x y => {
    if (_width <= 0. || _height <= 0.) {
      false
    }
    else {
      let normx = ((x -. _x) /. _width);
      let normy = ((y -. _y) /. _height);

      let normx = normx *. normx;
      let normy = normy *. normy;

      (normx +. normy) <= 1.;
    }
  };

  pub getBounds => {
    new rectangle x::(_x -. _width) y::(_y -. _height) width::_width height::_height ()
  }
};
