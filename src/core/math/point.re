class point ::x=0. ::y=0. () => {
  val mutable _x:float = x;
  val mutable _y:float = y;

  pub getX => {
    _x
  };

  pub getY => {
    _y
  };

  pub setX ::x => {
    _x = x;
  };

  pub setY ::y => {
    _y = y;
  };

  pub clone => {
    new point ::x ::y ();
  };

  pub copy (p:point) => {
    let x = p#getX;
    let y = p#getY;
    this#set ::x ::y ();
  };

  pub equals (p:point) => {
    _x === p#getX && _y === p#getY
  };

  pub set ::x=? ::y=? () => {
    _x = switch x {
      | Some x => x
      | None => 0.
    };
    _y = switch y {
      | Some y => y
      | None => switch x {
        | Some x => x
        | None => 0.
      }
    };
  };

};
