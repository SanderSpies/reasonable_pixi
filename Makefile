default:
	rebuild -clean
	rebuild -I src/core/math src/core/math/shapes/rectangle.native
	rebuild -I src/core/math src/core/math/matrix.native
	rebuild src/core/utils/utils.native
