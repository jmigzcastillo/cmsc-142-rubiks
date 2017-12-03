/**
 * GET /
 */
exports.index = function(req, res) {
  res.render('home', {
    title: 'Home'
  });
};

/**
 * POST /solvecube
 */
exports.solveCube = function(req, res) {
  // do solve here

  res.send({ msg:"success" });
}