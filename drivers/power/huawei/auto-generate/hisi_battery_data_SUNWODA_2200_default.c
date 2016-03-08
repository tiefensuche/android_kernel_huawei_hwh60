
/* DO NOT EDIT - Generated automatically by build.py */

static struct single_row_lut SUNWODA_2200_fcc_temp_default = {
	.x		= {-20, -10, 0, 25, 40, 60},
	.y		= {2206, 2220, 2192, 2207, 2192, 2182},
	.cols	= 6
};

static struct single_row_lut SUNWODA_2200_fcc_sf_default = {
	.x		= {0, 100, 200, 300, 400, 500},
	.y		= {100, 96, 94, 92, 90, 88},
	.cols	= 6
};

static struct sf_lut SUNWODA_2200_pc_sf_default = {
	.rows = 1,
	.cols = 1,
	.row_entries = {0},
	.percent = {100},
	.sf = {
		{100}
	}
};


static struct sf_lut SUNWODA_2200_rbatt_sf_default = {
	.rows = 28,
	.cols = 6,
	.row_entries = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf = {
		{3508, 2109, 1466, 277, 171, 140},
		{3507, 2109, 1466, 277, 171, 140},
		{3288, 2062, 1453, 282, 174, 140},
		{3177, 1995, 1421, 288, 177, 143},
		{3036, 2001, 1464, 295, 181, 145},
		{2762, 1812, 1290, 326, 187, 149},
		{2731, 1708, 1234, 324, 197, 153},
		{2715, 1702, 1219, 354, 212, 161},
		{2733, 1699, 1189, 325, 233, 179},
		{2773, 1698, 1160, 270, 182, 148},
		{2831, 1754, 1208, 257, 170, 142},
		{2899, 1818, 1281, 263, 173, 144},
		{2974, 1895, 1365, 269, 178, 147},
		{3086, 1980, 1475, 272, 186, 154},
		{3236, 2082, 1567, 280, 183, 152},
		{3402, 2236, 1674, 295, 176, 145},
		{3609, 2439, 1792, 304, 175, 142},
		{3852, 2679, 1977, 318, 178, 143},
		{5214, 3134, 2255, 324, 187, 146},
		{6657, 3447, 1945, 306, 184, 148},
		{7017, 3617, 2052, 311, 183, 149},
		{7477, 3911, 2264, 321, 181, 147},
		{7897, 4160, 2441, 323, 177, 148},
		{8338, 4340, 2596, 320, 177, 147},
		{8822, 4643, 2797, 330, 181, 147},
		{9400, 5064, 2987, 356, 187, 153},
		{10098, 5411, 3260, 389, 194, 158},
		{11308, 6071, 3756, 947, 224, 163},
	}
};

static struct pc_temp_ocv_lut SUNWODA_2200_pc_temp_ocv_default = {
	.rows = 29,
	.cols = 6,
	.temp = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv = {
		{4309, 4314, 4297, 4296, 4288, 4284},
		{4213, 4229, 4219, 4234, 4229, 4227},
		{4144, 4170, 4161, 4180, 4175, 4173},
		{4100, 4115, 4108, 4129, 4124, 4121},
		{4044, 4075, 4070, 4080, 4075, 4073},
		{3955, 3997, 3993, 4037, 4029, 4027},
		{3912, 3935, 3943, 3979, 3986, 3986},
		{3876, 3898, 3905, 3951, 3951, 3949},
		{3848, 3865, 3869, 3907, 3912, 3912},
		{3826, 3835, 3834, 3862, 3863, 3863},
		{3807, 3815, 3815, 3832, 3834, 3834},
		{3788, 3797, 3800, 3811, 3813, 3813},
		{3769, 3778, 3786, 3794, 3796, 3795},
		{3753, 3760, 3774, 3779, 3782, 3781},
		{3740, 3745, 3759, 3768, 3767, 3764},
		{3724, 3733, 3743, 3756, 3752, 3741},
		{3709, 3723, 3725, 3737, 3733, 3720},
		{3687, 3709, 3710, 3706, 3702, 3690},
		{3655, 3689, 3695, 3686, 3681, 3671},
		{3646, 3683, 3691, 3685, 3680, 3669},
		{3631, 3673, 3685, 3684, 3679, 3668},
		{3617, 3662, 3679, 3680, 3677, 3666},
		{3600, 3648, 3669, 3673, 3672, 3661},
		{3579, 3625, 3653, 3649, 3658, 3643},
		{3551, 3593, 3626, 3605, 3619, 3607},
		{3513, 3553, 3581, 3545, 3566, 3556},
		{3458, 3491, 3514, 3460, 3495, 3488},
		{3371, 3389, 3412, 3342, 3390, 3387},
		{3200, 3200, 3200, 3200, 3200, 3200},
	}
};

struct hisi_smartstar_coul_battery_data SUNWODA_2200_battery_data_default = {
	.id_voltage_min = 800,
	.id_voltage_max = 900,
	.fcc = 2200,
	.fcc_temp_lut  = &SUNWODA_2200_fcc_temp_default,
	.fcc_sf_lut = &SUNWODA_2200_fcc_sf_default,
	.pc_temp_ocv_lut = &SUNWODA_2200_pc_temp_ocv_default,
	.pc_sf_lut = &SUNWODA_2200_pc_sf_default,
	.rbatt_sf_lut = &SUNWODA_2200_rbatt_sf_default,
	.default_rbatt_mohm = 100,
	.max_currentmA = 1000,
    .max_voltagemV = 4352,
    .max_cin_currentmA = 1200,
    .terminal_currentmA = 100,
    .charge_in_temp_5 = 3,
    .charge_in_temp_10 = 3,
    .batt_brand = "Default",
};
