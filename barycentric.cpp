#include "ALFI/ALFI/ALFI/misc.h"

template alfi::DefaultContainer<double> alfi::misc::barycentric(
	const alfi::DefaultContainer<double>& X,
	const alfi::DefaultContainer<double>& Y,
	const alfi::DefaultContainer<double>& xx,
	alfi::dist::Type dist_type,
	const double& epsilon);