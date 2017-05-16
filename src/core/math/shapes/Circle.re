open Rectangle;

class circle ::x=0. ::y=0. ::radius=0. () => {
  val mutable _x:float = x;
  val mutable _y:float = y;
  val mutable _radius:float = radius;

  pub clone => {
    new circle x::_x y::_y radius::_radius ();
  };

  pub contains x y => {
    if (radius <= 0.) {
      false
    } else {
      let r2 = radius *. radius;
      let dx = _x -. x;
      let dy = _y -. y;

      let dx = dx *. dx;
      let dy = dy *. dy;

      ((dx +. dy) <= r2);
    }
  };

  pub getBounds => {
    new rectangle x::(_x -. _radius) y::(_y -. _radius) width::(_radius *. 2.) height::(_radius *. 2.) ()
  }
};
