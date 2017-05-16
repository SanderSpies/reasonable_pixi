
class matrix ::a=1. ::b=0. ::c=0. ::d=1. ::tx=0. ::ty=0. () => {
  val mutable _a:float = a;
  val mutable _b:float = b;
  val mutable _c:float = c;
  val mutable _d:float = d;
  val mutable _tx:float = tx;
  val mutable _ty:float = ty;
  val mutable _array:array float = [||];

  pub getA => {
    _a
  };

  pub getB => {
    _b
  };

  pub getC => {
    _c
  };

  pub getD => {
    _d
  };

  pub getTx => {
    _tx;
  };

  pub getTy => {
    _ty;
  };


  pub setA a => {
    _a = a;
  };

  pub setB b => {
    _b = b;
  };

  pub setC c => {
    _c = c;
  };

  pub setD d => {
    _d = d;
  };

  pub setTx tx => {
    _tx = tx;
  };

  pub setTy ty => {
    _ty = ty;
  };

  pub fromArray arr => {
    _a = arr.(0);
    _b = arr.(1);
    _c = arr.(2);
    _d = arr.(3);
    _tx = arr.(4);
    _ty = arr.(5);
  };

  pub set a b c d tx ty => {
    _a = a;
    _b = b;
    _c = c;
    _d = d;
    _tx = tx;
    _ty = ty;
    this
  };

  pub toArray ::transpose=false ::out=? () => {
    let array = switch out {
      | Some arr => arr
      | None => _array
    };
    if transpose {
      array.(0) = _a;
      array.(1) = _b;
      array.(2) = 0.;
      array.(3) = _c;
      array.(4) = _d;
      array.(5) = 0.;
      array.(6) = _tx;
      array.(7) = _ty;
      array.(8) = 1.;
    } else {
      array.(0) = _a;
      array.(1) = _c;
      array.(2) = _tx;
      array.(3) = _b;
      array.(4) = _d;
      array.(5) = _ty;
      array.(6) = 0.;
      array.(7) = 0.;
      array.(8) = 1.;
    };
    array
  };

  pub apply pos::(pos:Point.point) newPos::(newPos:option Point.point)=? () => {
    let newPos = switch newPos {
      | Some newPos => newPos
      | None => new Point.point()
    };
    let x = pos#getX;
    let y = pos#getY;

    newPos#setX((_a *. x) +. (_c *. y) +. _tx);
    newPos#setY((_b *. x) +. (_d *. y) +. _ty);
    newPos
  };

  pub applyInverse pos::(pos:Point.point) newPos::(newPos:option Point.point)=? () => {
    let newPos = switch newPos {
      | Some newPos => newPos
      | None => new Point.point()
    };
    let id = 1. /. ((_a *. _d) +. (_c *. (-._b)));

    let x = pos#getX;
    let y = pos#getY;

    newPos#setX ((_d *. id *. x) +. ((-._c) *. id *. y) +. (((_ty *. _c) -. (_tx *. _d)) *. id));
    newPos#setY ((_a *. id *. y) +. ((-._b) *. id *. x) +. ((((-._ty) *. _a) +. (_tx *. _b)) *. id));

    newPos
  };

  pub translate x y => {
    _tx = _tx +. x;
    _ty = _ty +. y;
    this
  };

  pub scale x y => {
    _a = _a *. x;
    _d = _d *. y;
    _c = _c *. x;
    _b = _b *. y;
    _tx = _tx *. x;
    _ty = _ty *. y;
    this
  };

  pub rotate angle => {
    let cosine = cos angle;
    let sine = sin angle;

    let a1 = _a;
    let c1 = _c;
    let tx1 = _tx;

    _a = (a1 *. cosine) -. (_b *. sine);
    _b = (a1 *. sine) +. (_b *. cosine);
    _c = (c1 *. cosine) -. (_d *. sine);
    _d = (c1 *. sine) +. (_d *. cosine);
    _tx = (tx1 *. cosine) -. (_ty *. sine);
    _ty = (tx1 *. sine) +. (_ty *. cosine);

    this
  };

  pub append (matrix:matrix) => {
    let a1 = _a;
    let b1 = _b;
    let c1 = _c;
    let d1 = _d;

    _a = (matrix#getA *. a1) +. (matrix#getB *. c1);
    _b = (matrix#getA *. b1) +. (matrix#getB *. d1);
    _c = (matrix#getC *. a1) +. (matrix#getD *. c1);
    _d = (matrix#getC *. b1) +. (matrix#getD *. d1);

    _tx = (matrix#getTx *. a1) +. (matrix#getTy *. c1) +. _tx;
    _ty = (matrix#getTx *. b1) +. (matrix#getTy *. d1) +. _ty;

    this
  };

  pub setTransform x y pivotX pivotY scaleX scaleY rotation skewX skewY => {
    let sr = sin rotation;
    let cr = cos rotation;
    let cy = cos skewY;
    let sy = sin skewY;
    let nsx = -.(sin skewX);
    let cx = cos skewX;

    let a = cr *. scaleX;
    let b = sr *. scaleX;
    let c = (-.sr) *. scaleY;
    let d =  cr *. scaleY;

    _a = (cy *. a) +. (sy *. c);
    _b = (cy *. b) +. (sy *. d);
    _c = (nsx *. a) +. (cx *. c);
    _d = (nsx *. b) +. (cx *. d);

    _tx = x +. ((pivotX *. a) +. (pivotY *. c));
    _ty = y +. ((pivotX *. b) +. (pivotY *. d));

    this
  };

  pub prepend (matrix:matrix) => {
    let tx1 = _tx;

    if (matrix#getA != 1. || matrix#getB != 0. || matrix#getC != 0. || matrix#getD != 1.) {
      let a1 = _a;
      let c1 = _c;

      _a = (a1 *. matrix#getA) +. (_b *. matrix#getC);
      _b = (a1 *. matrix#getB) +. (_b *. matrix#getD);
      _c = (c1 *. matrix#getA) +. (_d *. matrix#getC);
      _d = (c1 *. matrix#getB) +. (_d *. matrix#getD);
    };

    _tx = (tx1 *. matrix#getA) +. (_ty *. matrix#getC) +. matrix#getTx;
    _ty = (tx1 *. matrix#getB) +. (_ty *. matrix#getD) +. matrix#getTy;

    this
  };
/*
  pub decompose => {
    "not implemented yet"
  }; */

  pub invert => {
    let a1 = _a;
    let b1 = _b;
    let c1 = _c;
    let d1 = _d;
    let tx1 = _tx;
    let n = (a1 *. d1) -. (b1 *. c1);

    _a = d1 /. n;
    _b = (-.b1) /. n;
    _c = (-.c1) /. n;
    _d = a1 /. n;
    _tx = ((c1 *. _ty) -. (d1 *. tx1)) /. n;
    _ty = -.((a1 *. _ty) -. (b1 *. tx1)) /. n;

    this;
  };

  pub identity => {
    _a = 1.;
    _b = 0.;
    _c = 0.;
    _d = 1.;
    _tx = 0.;
    _ty = 0.;
    this;
  };

  pub clone => {
    new matrix a::_a b::_b c::_c d::_d tx::_tx ty::_ty ();
  };

  pub copy (matrix:matrix) => {
    matrix#setA _a;
    matrix#setB _b;
    matrix#setC _c;
    matrix#setD _d;
    matrix#setTx _tx;
    matrix#setTy _ty;

    matrix
  };

};

let identity = new matrix ();
let temp_matrix = new matrix ();
