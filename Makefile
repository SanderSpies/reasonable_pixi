default:
	rebuild -clean
	rebuild -I src/core/math src/core/math/shapes/rectangle.native
	rebuild -I src/core/math src/core/math/matrix.native
	rebuild -I src/core/math src/core/math/groupd8.native
	rebuild -I src/core/math src/core/math/shapes/circle.native
	rebuild -I src/core/math src/core/math/shapes/ellipse.native
	rebuild -I src/core/math src/core/math/shapes/polygon.native
	rebuild src/core/utils/utils.native
