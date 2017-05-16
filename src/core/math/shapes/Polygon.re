open Point;

class polygon points => {
  val mutable _points:list float = points;
  val mutable closed:bool = false;

  pub clone => {
    new polygon _points;
  };

  pub close => {
    if ((List.nth _points 0 != List.nth _points ((List.length _points) - 2)) || ((List.nth _points 1) != (List.nth _points ((List.length _points) - 1)))){
      _points = _points @ [(List.nth _points 0)];
      _points = _points @ [(List.nth _points 1)];
    }
  };

    pub contains () => {
      failwith "not implemented yet sorry";
      ();
    };

};
