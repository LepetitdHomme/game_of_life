#include "includes/common.h"

/*
** gaussian function:
** 1 / (sigma * sqrt(2 * M_PI)) * exp(-0.5 * pow((x - mu) / sigma, 2))
*/

void display_gauss(SDL_Renderer *renderer) {
	int i;
	double j;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	for (int u = WINDOW_WIDTH - 100; u < WINDOW_WIDTH ; u++) {
		for (int y = 0 ; y < 100 ; y++) {
			SDL_RenderDrawPoint(renderer, u, y);
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (i = 0; i < 802 ; i++) {
		j = gaussian(0, i);
		int c = (i * (double)(100.0 / 801.0)) + WINDOW_WIDTH - 100;
		int d = ((j+1) * (double)(10000.0/201.0) - 50)*2;
		
		SDL_RenderDrawPoint(renderer, c, 100-d);
	}
}

// void display_gauss(SDL_Renderer *renderer) {
// 	int i;
// 	double j;
// 	SDL_Rect rect;

// 	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // activates alpha blending for transparency
// 	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);

// 	rect.w = WINDOW_WIDTH / 10;
// 	rect.x = WINDOW_WIDTH - rect.w;
// 	rect.y = 0;
// 	rect.h = WINDOW_HEIGHT / 10;
// 	// printf("rect: %d | %d\n", rect.w, rect.h);
// 	SDL_RenderFillRect(renderer, &rect);

// 	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
// 	for (i = 0; i < 802 ; i++) {
// 		j = gaussian(0, i);
// 		int c = (i * (double)((double)rect.w / 801.0)) + rect.x;
// 		int d = (j+1) * (double)(10000.0/201.0);
// 		printf("%d, ", d);
// 		d = (d - rect.h) * 2;
// => ISSUE ON d;
// 		SDL_RenderDrawPoint(renderer, c, rect.h - d);

// 	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE); // deactivates alpha blending
// 	}
// }

double gaussian(int type, int x) {
	static double gauss[801] = { 0.0,
 0.0003358884248838177,
 0.00034842157506604965,
 0.0003634613552847281,
 0.0003785011355034065,
 0.00039354091572208486,
 0.0004085806959407633,
 0.0004261271061958881,
 0.0004436735164510129,
 0.00046121992670613773,
 0.00047876633696126254,
 0.0004988193772528337,
 0.000518872417544405,
 0.0005389254578359762,
 0.0005589784981275474,
 0.000581538168455565,
 0.0006040978387835826,
 0.0006291641391480465,
 0.0006517238094760641,
 0.0006792967398769745,
 0.0007043630402414386,
 0.000731935970642349,
 0.0007595089010432594,
 0.0007895884614806162,
 0.0008196680219179729,
 0.0008522542123917762,
 0.0008848404028655795,
 0.0009174265933393827,
 0.0009525194138496323,
 0.0009876122343598819,
 0.001025211684906578,
 0.00106531776548972,
 0.0011054238460728627,
 0.0011455299266560051,
 0.0011881426372755937,
 0.0012332619779316292,
 0.0012783813185876644,
 0.0013260072892801458,
 0.001376139890009074,
 0.0014262724907380018,
 0.0014789117215033764,
 0.0015340575823051972,
 0.001589203443107018,
 0.0016468559339452853,
 0.0017070150548199987,
 0.001769680805731159,
 0.0018348531866787653,
 0.0019000255676263718,
 0.0019677045786104246,
 0.00204039684966737,
 0.002113089120724316,
 0.002188288021817708,
 0.0022659935529475463,
 0.002346205714113831,
 0.0024289245053165623,
 0.00251414992655574,
 0.002601881977831364,
 0.0026946272891798808,
 0.002787372600528397,
 0.002885131171949807,
 0.0029853963734076633,
 0.0030881682049019657,
 0.003195953296469161,
 0.0033062450180728026,
 0.0034190433697128906,
 0.003536854981425871,
 0.0036571732231752987,
 0.0037799980949611723,
 0.003910342856856385,
 0.004040687618751598,
 0.0041785522707561504,
 0.004318923552797148,
 0.004461801464874592,
 0.004612199267061377,
 0.004765103699284607,
 0.004923021391580731,
 0.005085952343949747,
 0.005253896556391656,
 0.005426854028906457,
 0.005604824761494152,
 0.005787808754154739,
 0.0059758060068882185,
 0.006168816519694592,
 0.006369346922610304,
 0.006574890585598909,
 0.006785447508660407,
 0.007003524321831244,
 0.007229121025111419,
 0.007457224358428043,
 0.007695354211890449,
 0.007938497325425752,
 0.00818916032907039,
 0.008447343222824371,
 0.008710539376651241,
 0.0089837620506239,
 0.00926199798466945,
 0.009550260438860786,
 0.009846042783161462,
 0.010149345017571474,
 0.010460167142090828,
 0.010781015786755969,
 0.011109384321530448,
 0.01144777937645071,
 0.011793694321480315,
 0.012149635786655703,
 0.012515603771976878,
 0.012891598277443838,
 0.013275112673020138,
 0.013671160218778669,
 0.014077234284682986,
 0.014493334870733088,
 0.014921968606965423,
 0.015358122233307096,
 0.015809315639867448,
 0.016270535566573586,
 0.01674178201342551,
 0.017228068240496112,
 0.0177243809877125,
 0.018233226885111118,
 0.018757112562728415,
 0.019293531390527946,
 0.01983997673847326,
 0.0204039684966737,
 0.020980493405056373,
 0.021569551463621276,
 0.022173649302404858,
 0.022795293551443566,
 0.023429470950664506,
 0.024078688130104123,
 0.02474294508976242,
 0.02542474845967584,
 0.02612159160980794,
 0.026835981170195165,
 0.027565410510801067,
 0.028312386261662093,
 0.029076908422778245,
 0.029858976994149525,
 0.03066109860581237,
 0.0314782599976939,
 0.032315474429867,
 0.033172741902331666,
 0.03404755578505146,
 0.034942422708062824,
 0.03585734267136576,
 0.03679231567496027,
 0.03774984834888279,
 0.03872492743306044,
 0.03972507281760256,
 0.0407427646123998,
 0.0417855227075615,
 0.04285084047305122,
 0.04393621127883251,
 0.045046648384978266,
 0.04617964516145204,
 0.047337708238290276,
 0.048518330985456534,
 0.04972402003298725,
 0.05095477538088243,
 0.05221059702914208,
 0.05349399160780263,
 0.05479994585679121,
 0.056135979666217146,
 0.05749457314597109,
 0.0588832461861624,
 0.06029949215675461,
 0.06174080442771129,
 0.06321219625910533,
 0.06471366765093672,
 0.06624020534313259,
 0.06779932922580224,
 0.06938853266890926,
 0.0710053090424172,
 0.07265467160639892,
 0.07433411373081801,
 0.07604363541567445,
 0.07778574329100471,
 0.07956043735680875,
 0.08136521098305018,
 0.08320507742980182,
 0.08507753006702728,
 0.08698256889472655,
 0.08892270054293606,
 0.09089541838161938,
 0.09290322904081294,
 0.09494613252051677,
 0.09702412882073082,
 0.09913721794145515,
 0.10128790651272615,
 0.10347368790450741,
 0.10569456211679894,
 0.10795303577963714,
 0.1102516155230585,
 0.11258528808699007,
 0.11495656010146837,
 0.11736793819652981,
 0.11981691574213796,
 0.12230349273829279,
 0.12483017581503074,
 0.12739696497235187,
 0.13000386021025612,
 0.13264835489870708,
 0.1353354622977776,
 0.1380626757774313,
 0.14082999533766813,
 0.14363992760852454,
 0.1464899659599641,
 0.14938261702202324,
 0.15231537416466553,
 0.15529074401792742,
 0.15831123321184534,
 0.1613718284863464,
 0.164475036471467,
 0.16762085716720726,
 0.1708117972036035,
 0.17404284332058292,
 0.17731900877821838,
 0.18064029357650987,
 0.18400419108542093,
 0.18741070130495158,
 0.1908623308651383,
 0.194359079765981,
 0.19789844137744333,
 0.20148292232956166,
 0.20511252262233606,
 0.20878473562573005,
 0.21250206796978008,
 0.21626451965448612,
 0.22007209067984818,
 0.2239247810458663,
 0.227820084122504,
 0.23176050653979774,
 0.2357460482977475,
 0.23977670939635337,
 0.24384998320557874,
 0.24796837635546018,
 0.25213188884599763,
 0.25634052067719115,
 0.26059176521900423,
 0.2648881291014734,
 0.2692271056945621,
 0.2736112016283069,
 0.2780379102726712,
 0.2825072316276551,
 0.2870216723232951,
 0.2915787257295546,
 0.29617588521639737,
 0.3008181640438961,
 0.3055030555820144,
 0.3102280532007159,
 0.31499566353003694,
 0.3198033799399411,
 0.3246537090604649,
 0.3295416376315354,
 0.33447217891322545,
 0.3394428262754987,
 0.34445357971835505,
 0.3495019326117581,
 0.3545878849557078,
 0.3597139433802407,
 0.36487509462528384,
 0.3700763519509101,
 0.3753101954670102,
 0.3805841450636934,
 0.3858906808508505,
 0.3912348160885542,
 0.3966115375167317,
 0.40202084513538305,
 0.40746524557454467,
 0.41294223220418,
 0.41844929839425277,
 0.4239889507747993,
 0.42955868271578324,
 0.43515598758716806,
 0.4407833720189902,
 0.4464408360112498,
 0.45212336630387373,
 0.45783346952689863,
 0.46356863905028795,
 0.46932887487404185,
 0.4751141769981601,
 0.4809220387926064,
 0.4867524602573807,
 0.49260293476244665,
 0.4984759689378406,
 0.504369056153526,
 0.5102771831494303,
 0.5162053631856259,
 0.5221510896320768,
 0.5281118558587464,
 0.5340851552355982,
 0.5400734943926686,
 0.5460743666999213,
 0.5520877721573562,
 0.5581086975049004,
 0.564142156002627,
 0.5701831343904628,
 0.5762291260383715,
 0.5822826375763895,
 0.5883411623744805,
 0.594402193802608,
 0.6004657318607717,
 0.606531776548972,
 0.6125953146071358,
 0.6186588526652997,
 0.6247223907234636,
 0.6307784088915179,
 0.6368319204295361,
 0.6428779120774448,
 0.6489188904652806,
 0.6549473357029343,
 0.6609682610504785,
 0.6669766532478405,
 0.6729725122950203,
 0.6789558381920179,
 0.6849216176787603,
 0.690872357385284,
 0.6968055506815526,
 0.7027186909375297,
 0.7086092715231788,
 0.7144797990685363,
 0.7203277669435657,
 0.7261506685182307,
 0.7319459971624948,
 0.7377137528763579,
 0.7434539356598202,
 0.7491615322528087,
 0.7548390492853597,
 0.7604839801274371,
 0.766093818149004,
 0.7716685633500608,
 0.777205709100571,
 0.7827052554005343,
 0.7881646956199146,
 0.7935815231286754,
 0.7989557379268164,
 0.8042873400143379,
 0.8095713161311668,
 0.8148101729073399,
 0.8200014037128204,
 0.8251425019175719,
 0.8302334675215945,
 0.8352717938948518,
 0.8402549744073072,
 0.8451855156889974,
 0.8500584044798492,
 0.8548761474098991,
 0.8596337312190745,
 0.864331155907375,
 0.8689684214748008,
 0.8735430212913154,
 0.8780524487268826,
 0.882496703781502,
 0.886875786455174,
 0.8911896967478982,
 0.8954309147695655,
 0.8996044537802487,
 0.9037078071499114,
 0.9077384682485172,
 0.9116964370760661,
 0.9155792070025216,
 0.9193867780278837,
 0.9231166435221159,
 0.9267713101152548,
 0.9303457645472273,
 0.9338400068180336,
 0.93725654355771,
 0.9405878548761474,
 0.9438389540334183,
 0.9470073343994866,
 0.9500904893443157,
 0.9530859122378691,
 0.9559986163402199,
 0.9588235883912949,
 0.9615583217610579,
 0.9642078297095817,
 0.9667645923467572,
 0.9692336229326569,
 0.9716124148372445,
 0.9738984614304836,
 0.9760917627123741,
 0.9781923186829162,
 0.9802001293421098,
 0.9821126880599184,
 0.9839299948363421,
 0.9856545563014172,
 0.9872813591950709,
 0.9888129101473397,
 0.9902492091582235,
 0.9915852429676494,
 0.9928260248356903,
 0.9939690481323099,
 0.9950143128575081,
 0.9959593123812484,
 0.9968065533335673,
 0.9975535290844282,
 0.9982027462638678,
 0.9987516982418497,
 0.9992003850183736,
 0.999551313223476,
 0.9997994695970842,
 0.999949867399271,
 1.0,
 0.999949867399271,
 0.9997994695970842,
 0.999551313223476,
 0.9992003850183736,
 0.9987516982418497,
 0.9982027462638678,
 0.9975535290844282,
 0.9968065533335673,
 0.9959593123812484,
 0.9950143128575081,
 0.9939690481323099,
 0.9928260248356903,
 0.9915852429676494,
 0.9902492091582235,
 0.9888129101473397,
 0.9872813591950709,
 0.9856545563014172,
 0.9839299948363421,
 0.9821126880599184,
 0.9802001293421098,
 0.9781923186829162,
 0.9760917627123741,
 0.9738984614304836,
 0.9716124148372445,
 0.9692336229326569,
 0.9667645923467572,
 0.9642078297095817,
 0.9615583217610579,
 0.9588235883912949,
 0.9559986163402199,
 0.9530859122378691,
 0.9500904893443157,
 0.9470073343994866,
 0.9438389540334183,
 0.9405878548761474,
 0.93725654355771,
 0.9338400068180336,
 0.9303457645472273,
 0.9267713101152548,
 0.9231166435221159,
 0.9193867780278837,
 0.9155792070025216,
 0.9116964370760661,
 0.9077384682485172,
 0.9037078071499114,
 0.8996044537802487,
 0.8954309147695655,
 0.8911896967478982,
 0.886875786455174,
 0.882496703781502,
 0.8780524487268826,
 0.8735430212913154,
 0.8689684214748008,
 0.864331155907375,
 0.8596337312190745,
 0.8548761474098991,
 0.8500584044798492,
 0.8451855156889974,
 0.8402549744073072,
 0.8352717938948518,
 0.8302334675215945,
 0.8251425019175719,
 0.8200014037128204,
 0.8148101729073399,
 0.8095713161311668,
 0.8042873400143379,
 0.7989557379268164,
 0.7935815231286754,
 0.7881646956199146,
 0.7827052554005343,
 0.777205709100571,
 0.7716685633500608,
 0.766093818149004,
 0.7604839801274371,
 0.7548390492853597,
 0.7491615322528087,
 0.7434539356598202,
 0.7377137528763579,
 0.7319459971624948,
 0.7261506685182307,
 0.7203277669435657,
 0.7144797990685363,
 0.7086092715231788,
 0.7027186909375297,
 0.6968055506815526,
 0.690872357385284,
 0.6849216176787603,
 0.6789558381920179,
 0.6729725122950203,
 0.6669766532478405,
 0.6609682610504785,
 0.6549473357029343,
 0.6489188904652806,
 0.6428779120774448,
 0.6368319204295361,
 0.6307784088915179,
 0.6247223907234636,
 0.6186588526652997,
 0.6125953146071358,
 0.606531776548972,
 0.6004657318607717,
 0.594402193802608,
 0.5883411623744805,
 0.5822826375763895,
 0.5762291260383715,
 0.5701831343904628,
 0.564142156002627,
 0.5581086975049004,
 0.5520877721573562,
 0.5460743666999213,
 0.5400734943926686,
 0.5340851552355982,
 0.5281118558587464,
 0.5221510896320768,
 0.5162053631856259,
 0.5102771831494303,
 0.504369056153526,
 0.4984759689378406,
 0.49260293476244665,
 0.4867524602573807,
 0.4809220387926064,
 0.4751141769981601,
 0.46932887487404185,
 0.46356863905028795,
 0.45783346952689863,
 0.45212336630387373,
 0.4464408360112498,
 0.4407833720189902,
 0.43515598758716806,
 0.42955868271578324,
 0.4239889507747993,
 0.41844929839425277,
 0.41294223220418,
 0.40746524557454467,
 0.40202084513538305,
 0.3966115375167317,
 0.3912348160885542,
 0.3858906808508505,
 0.3805841450636934,
 0.3753101954670102,
 0.3700763519509101,
 0.36487509462528384,
 0.3597139433802407,
 0.3545878849557078,
 0.3495019326117581,
 0.34445357971835505,
 0.3394428262754987,
 0.33447217891322545,
 0.3295416376315354,
 0.3246537090604649,
 0.3198033799399411,
 0.31499566353003694,
 0.3102280532007159,
 0.3055030555820144,
 0.3008181640438961,
 0.29617588521639737,
 0.2915787257295546,
 0.2870216723232951,
 0.2825072316276551,
 0.2780379102726712,
 0.2736112016283069,
 0.2692271056945621,
 0.2648881291014734,
 0.26059176521900423,
 0.25634052067719115,
 0.25213188884599763,
 0.24796837635546018,
 0.24384998320557874,
 0.23977670939635337,
 0.2357460482977475,
 0.23176050653979774,
 0.227820084122504,
 0.2239247810458663,
 0.22007209067984818,
 0.21626451965448612,
 0.21250206796978008,
 0.20878473562573005,
 0.20511252262233606,
 0.20148292232956166,
 0.19789844137744333,
 0.194359079765981,
 0.1908623308651383,
 0.18741070130495158,
 0.18400419108542093,
 0.18064029357650987,
 0.17731900877821838,
 0.17404284332058292,
 0.1708117972036035,
 0.16762085716720726,
 0.164475036471467,
 0.1613718284863464,
 0.15831123321184534,
 0.15529074401792742,
 0.15231537416466553,
 0.14938261702202324,
 0.1464899659599641,
 0.14363992760852454,
 0.14082999533766813,
 0.1380626757774313,
 0.1353354622977776,
 0.13264835489870708,
 0.13000386021025612,
 0.12739696497235187,
 0.12483017581503074,
 0.12230349273829279,
 0.11981691574213796,
 0.11736793819652981,
 0.11495656010146837,
 0.11258528808699007,
 0.1102516155230585,
 0.10795303577963714,
 0.10569456211679894,
 0.10347368790450741,
 0.10128790651272615,
 0.09913721794145515,
 0.09702412882073082,
 0.09494613252051677,
 0.09290322904081294,
 0.09089541838161938,
 0.08892270054293606,
 0.08698256889472655,
 0.08507753006702728,
 0.08320507742980182,
 0.08136521098305018,
 0.07956043735680875,
 0.07778574329100471,
 0.07604363541567445,
 0.07433411373081801,
 0.07265467160639892,
 0.0710053090424172,
 0.06938853266890926,
 0.06779932922580224,
 0.06624020534313259,
 0.06471366765093672,
 0.06321219625910533,
 0.06174080442771129,
 0.06029949215675461,
 0.0588832461861624,
 0.05749457314597109,
 0.056135979666217146,
 0.05479994585679121,
 0.05349399160780263,
 0.05221059702914208,
 0.05095477538088243,
 0.04972402003298725,
 0.048518330985456534,
 0.047337708238290276,
 0.04617964516145204,
 0.045046648384978266,
 0.04393621127883251,
 0.04285084047305122,
 0.0417855227075615,
 0.0407427646123998,
 0.03972507281760256,
 0.03872492743306044,
 0.03774984834888279,
 0.03679231567496027,
 0.03585734267136576,
 0.034942422708062824,
 0.03404755578505146,
 0.033172741902331666,
 0.032315474429867,
 0.0314782599976939,
 0.03066109860581237,
 0.029858976994149525,
 0.029076908422778245,
 0.028312386261662093,
 0.027565410510801067,
 0.026835981170195165,
 0.02612159160980794,
 0.02542474845967584,
 0.02474294508976242,
 0.024078688130104123,
 0.023429470950664506,
 0.022795293551443566,
 0.022173649302404858,
 0.021569551463621276,
 0.020980493405056373,
 0.0204039684966737,
 0.01983997673847326,
 0.019293531390527946,
 0.018757112562728415,
 0.018233226885111118,
 0.0177243809877125,
 0.017228068240496112,
 0.01674178201342551,
 0.016270535566573586,
 0.015809315639867448,
 0.015358122233307096,
 0.014921968606965423,
 0.014493334870733088,
 0.014077234284682986,
 0.013671160218778669,
 0.013275112673020138,
 0.012891598277443838,
 0.012515603771976878,
 0.012149635786655703,
 0.011793694321480315,
 0.01144777937645071,
 0.011109384321530448,
 0.010781015786755969,
 0.010460167142090828,
 0.010149345017571474,
 0.009846042783161462,
 0.009550260438860786,
 0.00926199798466945,
 0.0089837620506239,
 0.008710539376651241,
 0.008447343222824371,
 0.00818916032907039,
 0.007938497325425752,
 0.007695354211890449,
 0.007457224358428043,
 0.007229121025111419,
 0.007003524321831244,
 0.006785447508660407,
 0.006574890585598909,
 0.006369346922610304,
 0.006168816519694592,
 0.0059758060068882185,
 0.005787808754154739,
 0.005604824761494152,
 0.005426854028906457,
 0.005253896556391656,
 0.005085952343949747,
 0.004923021391580731,
 0.004765103699284607,
 0.004612199267061377,
 0.004461801464874592,
 0.004318923552797148,
 0.0041785522707561504,
 0.004040687618751598,
 0.003910342856856385,
 0.0037799980949611723,
 0.0036571732231752987,
 0.003536854981425871,
 0.0034190433697128906,
 0.0033062450180728026,
 0.003195953296469161,
 0.0030881682049019657,
 0.0029853963734076633,
 0.002885131171949807,
 0.002787372600528397,
 0.0026946272891798808,
 0.002601881977831364,
 0.00251414992655574,
 0.0024289245053165623,
 0.002346205714113831,
 0.0022659935529475463,
 0.002188288021817708,
 0.002113089120724316,
 0.00204039684966737,
 0.0019677045786104246,
 0.0019000255676263718,
 0.0018348531866787653,
 0.001769680805731159,
 0.0017070150548199987,
 0.0016468559339452853,
 0.001589203443107018,
 0.0015340575823051972,
 0.0014789117215033764,
 0.0014262724907380018,
 0.001376139890009074,
 0.0013260072892801458,
 0.0012783813185876644,
 0.0012332619779316292,
 0.0011881426372755937,
 0.0011455299266560051,
 0.0011054238460728627,
 0.00106531776548972,
 0.001025211684906578,
 0.0009876122343598819,
 0.0009525194138496323,
 0.0009174265933393827,
 0.0008848404028655795,
 0.0008522542123917762,
 0.0008196680219179729,
 0.0007895884614806162,
 0.0007595089010432594,
 0.000731935970642349,
 0.0007043630402414386,
 0.0006792967398769745,
 0.0006517238094760641,
 0.0006291641391480465,
 0.0006040978387835826,
 0.000581538168455565,
 0.0005589784981275474,
 0.0005389254578359762,
 0.000518872417544405,
 0.0004988193772528337,
 0.00047876633696126254,
 0.00046121992670613773,
 0.0004436735164510129,
 0.0004261271061958881,
 0.0004085806959407633,
 0.00039354091572208486,
 0.0003785011355034065,
 0.0003634613552847281,
 0.00034842157506604965 };
	static double gauss1[801] = {
		-1.0,
		-0.999732,
		-0.999722,
		-0.99971,
		-0.999698,
		-0.999686,
		-0.999674,
		-0.99966,
		-0.999646,
		-0.999632,
		-0.999618,
		-0.999602,
		-0.999586,
		-0.99957,
		-0.999554,
		-0.999536,
		-0.999518,
		-0.999498,
		-0.99948,
		-0.999458,
		-0.999438,
		-0.999416,
		-0.999394,
		-0.99937,
		-0.999346,
		-0.99932,
		-0.999294,
		-0.999268,
		-0.99924,
		-0.999212,
		-0.999182,
		-0.99915,
		-0.999118,
		-0.999086,
		-0.999052,
		-0.999016,
		-0.99898,
		-0.998942,
		-0.998902,
		-0.998862,
		-0.99882,
		-0.998776,
		-0.998732,
		-0.998686,
		-0.998638,
		-0.998588,
		-0.998536,
		-0.998484,
		-0.99843,
		-0.998372,
		-0.998314,
		-0.998254,
		-0.998192,
		-0.998128,
		-0.998062,
		-0.997994,
		-0.997924,
		-0.99785,
		-0.997776,
		-0.997698,
		-0.997618,
		-0.997536,
		-0.99745,
		-0.997362,
		-0.997272,
		-0.997178,
		-0.997082,
		-0.996984,
		-0.99688,
		-0.996776,
		-0.996666,
		-0.996554,
		-0.99644,
		-0.99632,
		-0.996198,
		-0.996072,
		-0.995942,
		-0.995808,
		-0.99567,
		-0.995528,
		-0.995382,
		-0.995232,
		-0.995078,
		-0.994918,
		-0.994754,
		-0.994586,
		-0.994412,
		-0.994232,
		-0.99405,
		-0.99386,
		-0.993666,
		-0.993466,
		-0.99326,
		-0.99305,
		-0.992832,
		-0.99261,
		-0.99238,
		-0.992144,
		-0.991902,
		-0.991654,
		-0.991398,
		-0.991136,
		-0.990866,
		-0.99059,
		-0.990306,
		-0.990014,
		-0.989714,
		-0.989408,
		-0.989092,
		-0.988768,
		-0.988436,
		-0.988094,
		-0.987746,
		-0.987386,
		-0.987018,
		-0.986642,
		-0.986254,
		-0.985858,
		-0.985452,
		-0.985034,
		-0.984606,
		-0.98417,
		-0.98372,
		-0.98326,
		-0.98279,
		-0.982308,
		-0.981812,
		-0.981306,
		-0.980788,
		-0.980258,
		-0.979714,
		-0.979158,
		-0.978588,
		-0.978006,
		-0.97741,
		-0.9768,
		-0.976176,
		-0.975536,
		-0.974884,
		-0.974216,
		-0.973532,
		-0.972834,
		-0.97212,
		-0.97139,
		-0.970644,
		-0.96988,
		-0.969102,
		-0.968304,
		-0.967492,
		-0.96666,
		-0.9658100000000001,
		-0.964944,
		-0.964058,
		-0.963154,
		-0.96223,
		-0.961288,
		-0.960326,
		-0.959344,
		-0.958342,
		-0.957318,
		-0.956276,
		-0.95521,
		-0.954126,
		-0.953018,
		-0.951888,
		-0.950738,
		-0.949564,
		-0.948366,
		-0.947148,
		-0.945904,
		-0.944636,
		-0.943346,
		-0.94203,
		-0.94069,
		-0.939326,
		-0.937936,
		-0.93652,
		-0.93508,
		-0.933612,
		-0.932118,
		-0.930598,
		-0.92905,
		-0.927476,
		-0.925874,
		-0.924244,
		-0.922586,
		-0.9209,
		-0.919184,
		-0.91744,
		-0.915668,
		-0.913866,
		-0.912032,
		-0.91017,
		-0.908278,
		-0.906354,
		-0.9044,
		-0.902416,
		-0.9004,
		-0.898352,
		-0.896272,
		-0.894162,
		-0.892018,
		-0.889842,
		-0.887634,
		-0.885392,
		-0.883118,
		-0.88081,
		-0.87847,
		-0.876096,
		-0.873686,
		-0.871244,
		-0.868768,
		-0.866258,
		-0.863712,
		-0.8611340000000001,
		-0.85852,
		-0.85587,
		-0.853186,
		-0.850468,
		-0.847714,
		-0.844924,
		-0.8421,
		-0.83924,
		-0.836344,
		-0.833414,
		-0.830448,
		-0.827446,
		-0.824408,
		-0.821334,
		-0.818226,
		-0.815082,
		-0.811902,
		-0.808686,
		-0.805436,
		-0.80215,
		-0.798828,
		-0.79547,
		-0.7920780000000001,
		-0.78865,
		-0.785188,
		-0.78169,
		-0.778158,
		-0.774592,
		-0.7709900000000001,
		-0.767354,
		-0.763686,
		-0.7599819999999999,
		-0.756244,
		-0.752474,
		-0.74867,
		-0.744834,
		-0.740964,
		-0.7370639999999999,
		-0.7331300000000001,
		-0.7291639999999999,
		-0.725166,
		-0.7211380000000001,
		-0.7170799999999999,
		-0.71299,
		-0.708872,
		-0.7047220000000001,
		-0.700546,
		-0.696338,
		-0.692104,
		-0.68784,
		-0.68355,
		-0.679234,
		-0.67489,
		-0.67052,
		-0.666126,
		-0.661706,
		-0.657262,
		-0.6527959999999999,
		-0.648306,
		-0.6437919999999999,
		-0.639258,
		-0.634702,
		-0.630126,
		-0.6255299999999999,
		-0.620914,
		-0.6162799999999999,
		-0.6116280000000001,
		-0.6069599999999999,
		-0.602274,
		-0.597572,
		-0.592858,
		-0.588128,
		-0.583384,
		-0.5786279999999999,
		-0.573862,
		-0.5690839999999999,
		-0.564296,
		-0.559498,
		-0.554694,
		-0.5498799999999999,
		-0.54506,
		-0.5402359999999999,
		-0.535406,
		-0.530572,
		-0.525736,
		-0.5208980000000001,
		-0.516058,
		-0.51122,
		-0.506382,
		-0.501544,
		-0.49671200000000004,
		-0.49188200000000004,
		-0.487058,
		-0.48223800000000006,
		-0.47742799999999996,
		-0.47262400000000004,
		-0.46782999999999997,
		-0.46304599999999996,
		-0.458272,
		-0.453512,
		-0.44876400000000005,
		-0.44403000000000004,
		-0.43931200000000004,
		-0.434612,
		-0.429928,
		-0.42526200000000003,
		-0.420616,
		-0.41599200000000003,
		-0.41139000000000003,
		-0.40681,
		-0.40225599999999995,
		-0.397726,
		-0.39322199999999996,
		-0.38874600000000004,
		-0.38429800000000003,
		-0.37988,
		-0.37549200000000005,
		-0.371136,
		-0.366814,
		-0.362526,
		-0.35827200000000003,
		-0.35405600000000004,
		-0.34987599999999996,
		-0.345734,
		-0.34163200000000005,
		-0.33757000000000004,
		-0.33355,
		-0.32957400000000003,
		-0.32564000000000004,
		-0.32175200000000004,
		-0.31790799999999997,
		-0.31411199999999995,
		-0.310364,
		-0.30666400000000005,
		-0.303014,
		-0.299416,
		-0.29586999999999997,
		-0.29237599999999997,
		-0.288934,
		-0.28554999999999997,
		-0.28222,
		-0.278946,
		-0.27573000000000003,
		-0.27257200000000004,
		-0.269474,
		-0.266436,
		-0.26346,
		-0.260544,
		-0.25769200000000003,
		-0.254904,
		-0.252178,
		-0.24951999999999996,
		-0.24692599999999998,
		-0.244398,
		-0.241938,
		-0.23954799999999998,
		-0.237224,
		-0.23497,
		-0.232788,
		-0.23067400000000005,
		-0.228634,
		-0.22666399999999998,
		-0.22476600000000002,
		-0.22294199999999997,
		-0.22119200000000006,
		-0.21951600000000004,
		-0.21791400000000005,
		-0.21638800000000002,
		-0.21493799999999996,
		-0.21356200000000003,
		-0.212264,
		-0.21104199999999995,
		-0.20989599999999997,
		-0.20882999999999996,
		-0.20784000000000002,
		-0.206928,
		-0.206094,
		-0.20533999999999997,
		-0.20466399999999996,
		-0.20406800000000003,
		-0.20355,
		-0.20311199999999996,
		-0.202754,
		-0.20247400000000004,
		-0.202276,
		-0.202156,
		-0.20211599999999996,
		-0.202156,
		-0.202276,
		-0.20247400000000004,
		-0.202754,
		-0.20311199999999996,
		-0.20355,
		-0.20406800000000003,
		-0.20466399999999996,
		-0.20533999999999997,
		-0.206094,
		-0.206928,
		-0.20784000000000002,
		-0.20882999999999996,
		-0.20989599999999997,
		-0.21104199999999995,
		-0.212264,
		-0.21356200000000003,
		-0.21493799999999996,
		-0.21638800000000002,
		-0.21791400000000005,
		-0.21951600000000004,
		-0.22119200000000006,
		-0.22294199999999997,
		-0.22476600000000002,
		-0.22666399999999998,
		-0.228634,
		-0.23067400000000005,
		-0.232788,
		-0.23497,
		-0.237224,
		-0.23954799999999998,
		-0.241938,
		-0.244398,
		-0.24692599999999998,
		-0.24951999999999996,
		-0.252178,
		-0.254904,
		-0.25769200000000003,
		-0.260544,
		-0.26346,
		-0.266436,
		-0.269474,
		-0.27257200000000004,
		-0.27573000000000003,
		-0.278946,
		-0.28222,
		-0.28554999999999997,
		-0.288934,
		-0.29237599999999997,
		-0.29586999999999997,
		-0.299416,
		-0.303014,
		-0.30666400000000005,
		-0.310364,
		-0.31411199999999995,
		-0.31790799999999997,
		-0.32175200000000004,
		-0.32564000000000004,
		-0.32957400000000003,
		-0.33355,
		-0.33757000000000004,
		-0.34163200000000005,
		-0.345734,
		-0.34987599999999996,
		-0.35405600000000004,
		-0.35827200000000003,
		-0.362526,
		-0.366814,
		-0.371136,
		-0.37549200000000005,
		-0.37988,
		-0.38429800000000003,
		-0.38874600000000004,
		-0.39322199999999996,
		-0.397726,
		-0.40225599999999995,
		-0.40681,
		-0.41139000000000003,
		-0.41599200000000003,
		-0.420616,
		-0.42526200000000003,
		-0.429928,
		-0.434612,
		-0.43931200000000004,
		-0.44403000000000004,
		-0.44876400000000005,
		-0.453512,
		-0.458272,
		-0.46304599999999996,
		-0.46782999999999997,
		-0.47262400000000004,
		-0.47742799999999996,
		-0.48223800000000006,
		-0.487058,
		-0.49188200000000004,
		-0.49671200000000004,
		-0.501544,
		-0.506382,
		-0.51122,
		-0.516058,
		-0.5208980000000001,
		-0.525736,
		-0.530572,
		-0.535406,
		-0.5402359999999999,
		-0.54506,
		-0.5498799999999999,
		-0.554694,
		-0.559498,
		-0.564296,
		-0.5690839999999999,
		-0.573862,
		-0.5786279999999999,
		-0.583384,
		-0.588128,
		-0.592858,
		-0.597572,
		-0.602274,
		-0.6069599999999999,
		-0.6116280000000001,
		-0.6162799999999999,
		-0.620914,
		-0.6255299999999999,
		-0.630126,
		-0.634702,
		-0.639258,
		-0.6437919999999999,
		-0.648306,
		-0.6527959999999999,
		-0.657262,
		-0.661706,
		-0.666126,
		-0.67052,
		-0.67489,
		-0.679234,
		-0.68355,
		-0.68784,
		-0.692104,
		-0.696338,
		-0.700546,
		-0.7047220000000001,
		-0.708872,
		-0.71299,
		-0.7170799999999999,
		-0.7211380000000001,
		-0.725166,
		-0.7291639999999999,
		-0.7331300000000001,
		-0.7370639999999999,
		-0.740964,
		-0.744834,
		-0.74867,
		-0.752474,
		-0.756244,
		-0.7599819999999999,
		-0.763686,
		-0.767354,
		-0.7709900000000001,
		-0.774592,
		-0.778158,
		-0.78169,
		-0.785188,
		-0.78865,
		-0.7920780000000001,
		-0.79547,
		-0.798828,
		-0.80215,
		-0.805436,
		-0.808686,
		-0.811902,
		-0.815082,
		-0.818226,
		-0.821334,
		-0.824408,
		-0.827446,
		-0.830448,
		-0.833414,
		-0.836344,
		-0.83924,
		-0.8421,
		-0.844924,
		-0.847714,
		-0.850468,
		-0.853186,
		-0.85587,
		-0.85852,
		-0.8611340000000001,
		-0.863712,
		-0.866258,
		-0.868768,
		-0.871244,
		-0.873686,
		-0.876096,
		-0.87847,
		-0.88081,
		-0.883118,
		-0.885392,
		-0.887634,
		-0.889842,
		-0.892018,
		-0.894162,
		-0.896272,
		-0.898352,
		-0.9004,
		-0.902416,
		-0.9044,
		-0.906354,
		-0.908278,
		-0.91017,
		-0.912032,
		-0.913866,
		-0.915668,
		-0.91744,
		-0.919184,
		-0.9209,
		-0.922586,
		-0.924244,
		-0.925874,
		-0.927476,
		-0.92905,
		-0.930598,
		-0.932118,
		-0.933612,
		-0.93508,
		-0.93652,
		-0.937936,
		-0.939326,
		-0.94069,
		-0.94203,
		-0.943346,
		-0.944636,
		-0.945904,
		-0.947148,
		-0.948366,
		-0.949564,
		-0.950738,
		-0.951888,
		-0.953018,
		-0.954126,
		-0.95521,
		-0.956276,
		-0.957318,
		-0.958342,
		-0.959344,
		-0.960326,
		-0.961288,
		-0.96223,
		-0.963154,
		-0.964058,
		-0.964944,
		-0.9658100000000001,
		-0.96666,
		-0.967492,
		-0.968304,
		-0.969102,
		-0.96988,
		-0.970644,
		-0.97139,
		-0.97212,
		-0.972834,
		-0.973532,
		-0.974216,
		-0.974884,
		-0.975536,
		-0.976176,
		-0.9768,
		-0.97741,
		-0.978006,
		-0.978588,
		-0.979158,
		-0.979714,
		-0.980258,
		-0.980788,
		-0.981306,
		-0.981812,
		-0.982308,
		-0.98279,
		-0.98326,
		-0.98372,
		-0.98417,
		-0.984606,
		-0.985034,
		-0.985452,
		-0.985858,
		-0.986254,
		-0.986642,
		-0.987018,
		-0.987386,
		-0.987746,
		-0.988094,
		-0.988436,
		-0.988768,
		-0.989092,
		-0.989408,
		-0.989714,
		-0.990014,
		-0.990306,
		-0.99059,
		-0.990866,
		-0.991136,
		-0.991398,
		-0.991654,
		-0.991902,
		-0.992144,
		-0.99238,
		-0.99261,
		-0.992832,
		-0.99305,
		-0.99326,
		-0.993466,
		-0.993666,
		-0.99386,
		-0.99405,
		-0.994232,
		-0.994412,
		-0.994586,
		-0.994754,
		-0.994918,
		-0.995078,
		-0.995232,
		-0.995382,
		-0.995528,
		-0.99567,
		-0.995808,
		-0.995942,
		-0.996072,
		-0.996198,
		-0.99632,
		-0.99644,
		-0.996554,
		-0.996666,
		-0.996776,
		-0.99688,
		-0.996984,
		-0.997082,
		-0.997178,
		-0.997272,
		-0.997362,
		-0.99745,
		-0.997536,
		-0.997618,
		-0.997698,
		-0.997776,
		-0.99785,
		-0.997924,
		-0.997994,
		-0.998062,
		-0.998128,
		-0.998192,
		-0.998254,
		-0.998314,
		-0.998372,
		-0.99843,
		-0.998484,
		-0.998536,
		-0.998588,
		-0.998638,
		-0.998686,
		-0.998732,
		-0.998776,
		-0.99882,
		-0.998862,
		-0.998902,
		-0.998942,
		-0.99898,
		-0.999016,
		-0.999052,
		-0.999086,
		-0.999118,
		-0.99915,
		-0.999182,
		-0.999212,
		-0.99924,
		-0.999268,
		-0.999294,
		-0.99932,
		-0.999346,
		-0.99937,
		-0.999394,
		-0.999416,
		-0.999438,
		-0.999458,
		-0.99948,
		-0.999498,
		-0.999518,
		-0.999536,
		-0.999554,
		-0.99957,
		-0.999586,
		-0.999602,
		-0.999618,
		-0.999632,
		-0.999646,
		-0.99966,
		-0.999674,
		-0.999686,
		-0.999698,
		-0.99971,
		-0.999722
	};

	if (type == 0)
		return gauss[x];
	if (type == 1)
		return gauss1[(int)x];
}

int next_cycle_lenia(float (*grid)[GRID_H], float (*grid2)[GRID_H], state_t *state){
	int cells_count = 0;
	int radius = state->kernel_lenia.radius;
	int diameter = radius * 2;

  // Convolution with the kernel
  for (int x = radius; x < GRID_W - radius; x++) {
    for (int y = radius; y < GRID_H - radius; y++) {
      float sum = 0.0;

      for (int i = -radius; i < radius; i++) {
        for (int j = -radius; j < radius; j++) {
          sum += grid[x + i][y + j] * state->kernel_lenia.data[i + radius][j + radius];
        }
	    }
			// Apply growth rules
			grid2[x][y] = grid[x][y] + (sum >= 0.12 && sum <= 0.15 ? 0.1 : -0.1);
			// Ensure the value is within [0, 1]
			grid2[x][y] = fmin(fmax(grid2[x][y], 0.0), 1.0);
			if (grid2[x][y] > 0.0) {
				cells_count++;
			}
		}
	}
	return cells_count;
}
