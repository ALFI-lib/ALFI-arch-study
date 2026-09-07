#include "ALFI/ALFI/ALFI.h"

//// SPLINES
// Cubic
template class alfi::spline::CubicSpline<double>;

// Hermite
template class alfi::spline::HermiteSpline<double>;

// Linear
template class alfi::spline::LinearSpline<double>;

// PolyEqv
template class alfi::spline::PolyEqvSpline<double>;

// Quadratic
template class alfi::spline::QuadraticSpline<double>;

// Step
template class alfi::spline::StepSpline<double>;

//// DIST
template alfi::DefaultContainer<double> alfi::dist::uniform(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::quadratic(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::cubic(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_stretched(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_augmented(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_2(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_3(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_3_stretched(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_4(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_4_stretched(alfi::SizeT n, const double& a, const double& b);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_stretched(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_augmented(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_2(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_3(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_3_stretched(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_4(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::chebyshev_ellipse_4_stretched(alfi::SizeT n, const double& a, const double& b, const double& ratio);
template alfi::DefaultContainer<double> alfi::dist::logistic(alfi::SizeT n, const double& a, const double& b, const double& steepness);
template alfi::DefaultContainer<double> alfi::dist::logistic_stretched(alfi::SizeT n, const double& a, const double& b, const double& steepness);
template alfi::DefaultContainer<double> alfi::dist::erf(alfi::SizeT n, const double& a, const double& b, const double& steepness);
template alfi::DefaultContainer<double> alfi::dist::erf_stretched(alfi::SizeT n, const double& a, const double& b, const double& steepness);

//// MISC
template alfi::DefaultContainer<double> alfi::misc::barycentric(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y,
	const alfi::DefaultContainer<double>& xx,
	alfi::dist::Type dist_type,
	const double& epsilon);

//// POLY
template double alfi::poly::val(const alfi::DefaultContainer<double>& coeffs, const double& x);
template alfi::DefaultContainer<double> alfi::poly::val(const alfi::DefaultContainer<double>& coeffs, const alfi::DefaultContainer<double>& x);

template alfi::DefaultContainer<double> alfi::poly::lagrange<double>(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y);

template alfi::DefaultContainer<double> alfi::poly::lagrange_vals<double>(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y,
	const alfi::DefaultContainer<double>& xx);

template alfi::DefaultContainer<double> alfi::poly::imp_lagrange<double>(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y);

template alfi::DefaultContainer<double> alfi::poly::imp_lagrange_vals<double>(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y,
	const alfi::DefaultContainer<double>& xx,
	const double& epsilon);

template alfi::DefaultContainer<double> alfi::poly::newton<double>(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y);

template alfi::DefaultContainer<double> alfi::poly::newton_vals<double>(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y,
	const alfi::DefaultContainer<double>& xx);

//// RATF
template double alfi::ratf::val_mul(const alfi::ratf::RationalFunction<double>& rf, const double& x);
template alfi::DefaultContainer<double> alfi::ratf::val_mul(const alfi::ratf::RationalFunction<double>& rf, const alfi::DefaultContainer<double>& xx);

template double alfi::ratf::val_div(const alfi::ratf::RationalFunction<double>& rf, const double& x);
template alfi::DefaultContainer<double> alfi::ratf::val_div(const alfi::ratf::RationalFunction<double>& rf, const alfi::DefaultContainer<double>& xx);

template double alfi::ratf::val(const alfi::ratf::RationalFunction<double>& rf, const double& x);
template alfi::DefaultContainer<double> alfi::ratf::val(const alfi::ratf::RationalFunction<double>& rf, const alfi::DefaultContainer<double>& xx);

template alfi::ratf::RationalFunction<double> alfi::ratf::pade(alfi::DefaultContainer<double> P, alfi::SizeT n, alfi::SizeT m, const double& epsilon);