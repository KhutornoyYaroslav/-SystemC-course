
#include "systemc.h"

SC_MODULE(RAM) 
{
    //--------------------Ports Here-----------------------
    sc_in_clk clock;  
    sc_in<bool> reset;	
	sc_in<bool> in_write_enable_1;
	sc_in<bool> in_read_enable_1;
	sc_out<bool> out_ack_1;
	sc_in<sc_uint<32> > in_adrress_1;
	sc_in<sc_int<32> > in_data_1;
	sc_out<sc_int<32> > out_data_1;
	sc_in<bool> in_write_enable_2;
	sc_in<bool> in_read_enable_2;
	sc_out<bool> out_ack_2;
	sc_in<sc_uint<32> > in_adrress_2;
	sc_in<sc_int<32> > in_data_2;
	sc_out<sc_int<32> > out_data_2;

    //------------Local Variables Here---------------------
	int memory[4096];

    //------------Code Starts Here-------------------------
    void ram_action_1();
    void ram_action_2();   

    //------------Constructor Here-------------------------   
    SC_CTOR(RAM) : 

		clock("clock"), 
		reset("reset"),
		in_write_enable_1("in_write_enable_1"),
		in_read_enable_1("in_read_enable_1"),
		out_ack_1("out_ack_1"),
		in_adrress_1("in_adrress_1"),
		in_data_1("in_data_1"),
		out_data_1("out_data_1"),
		in_write_enable_2("in_write_enable_2"),
		in_read_enable_2("in_read_enable_2"),
		out_ack_2("out_ack_2"),
		in_adrress_2("in_adrress_2"),
		in_data_2("in_data_2"),
		out_data_2("out_data_2")

    {
		for(int i=0; i<4096; i++)
		{
			memory[i] =  -i;
		}

		memory[0] = 1610613236; //JMP to 500 Программа сортировки
		//memory[0] = 1610613336; //JMP to 600 Программа умножения
		//memory[0] = 1610613436; //JMP to 700 Программа фильтра

		memory[40] = 1342177536;
		memory[41] = 1343229696;
		memory[42] = 4026531840;
		memory[43] = 4026531840;
		memory[44] = 4026531840;
		memory[45] = 538968065;
		memory[46] = 303038465;
		memory[47] = 335544320;
		memory[48] = 4026531840;
		memory[49] = 1879048237;
		//memory[50] = 1610613502; //JMP to 766 - для работы с программой фильтрации
		memory[50] = 3221225472; // STOP - для сортировки и умножения

		memory[60] = 1342177536;
		memory[61] = 1343229696;
		memory[62] = 4026531840;
		memory[63] = 4026531840;
		memory[64] = 4026531840;
		memory[65] = 538968065;
		memory[66] = 303038465;
		memory[67] = 335544320;
		memory[68] = 4026531840;
		memory[69] = 1879048257;
		memory[70] = 1610613506;

		memory[80] = 1342177536;
		memory[81] = 1343229696;
		memory[82] = 4026531840;
		memory[83] = 4026531840;
		memory[84] = 4026531840;
		memory[85] = 538968065;
		memory[86] = 303038465;
		memory[87] = 335544320;
		memory[88] = 4026531840;
		memory[89] = 1879048277; 
		memory[90] = 1610613534;


		//Программа сортировки массива
		memory[500] = 1342177355; // Количество элементов 76 (загружаем 76-1)
		memory[501] = 1344276932; // Начальный адрес = 2500 
		memory[502] = 4026531840;
		memory[503] = 4026531840;
		memory[504] = 4026531840;
		memory[505] = 1074790400;
		memory[506] = 540016642;
		memory[507] = 304087042; 
		memory[508] = 4026531840;
		memory[509] = 4026531840;
		memory[510] = 4026531840;
		memory[511] = 541065218;
		memory[512] = 4026531841; 
		memory[513] = 4026531842;
		memory[514] = 4026531843;
		memory[515] = 99614820;
		memory[516] = 2415919633;
		memory[517] = 1078984708;
		memory[518] = 1077936131;
		memory[519] = 4026531840;
		memory[520] = 4026531840;
		memory[521] = 1076887557;
		memory[522] = 805306498;
		memory[523] = 337641474;
		memory[524] = 4026531840;
		memory[525] = 4026531840;
		memory[526] = 4026531840;
		memory[527] = 805306466;
		memory[528] = 304087042;
		memory[529] = 336592897;
		memory[530] = 4026531840;
		memory[531] = 1879048698;
		memory[532] = 335544320;
		memory[533] = 4026531840;
		memory[534] = 1879048693;
		memory[535] = 1610612776; //JMP to 40 - для работы с программой сортировки
		//memory[535] = 1610613504; //JMP to 768 - для работы с программой фильтрации

	//Программа умножения матриц
		memory[600] = 1342177285;
		memory[601] = 1343225866;
		memory[602] = 1344274436;
		memory[603] = 1358956496;
		memory[604] = 1360005272;
		memory[605] = 1361054048;
		memory[606] = 1345323008;
		memory[607] = 1346371584;
		memory[608] = 1347420160;
		memory[609] = 4026531840;
		memory[610] = 4026531840;
		memory[611] = 106954850;
		memory[612] = 108003425;
		memory[613] = 109052066;
		memory[614] = 4026531840;
		memory[615] = 4026531840;
		memory[616] = 39846084;
		memory[617] = 40894693;
		memory[618] = 41943300;
		memory[619] = 4026531840;
		memory[620] = 4026531840;
		memory[621] = 39846096;
		memory[622] = 40894705;
		memory[623] = 41943314;
		memory[624] = 4026531840;
		memory[625] = 4026531840;
		memory[626] = 546308102;
		memory[627] = 547356679;
		memory[628] = 548405256;
		memory[629] = 4026531840;
		memory[630] = 4026531840;
		memory[631] = 4026531840;
		memory[632] = 113246539;
		memory[633] = 4026531840;
		memory[634] = 4026531840;
		memory[635] = 4026531840;
		memory[636] = 42991916;
		memory[637] = 4026531840;
		memory[638] = 4026531840;
		memory[639] = 4026531840;	
		memory[640] = 805306662;
		memory[641] = 307232773;
		memory[642] = 4026531840;
		memory[643] = 4026531840;
		memory[644] = 4026531840;
		memory[645] = 99614881;
		memory[646] = 1879048803;
		memory[647] = 306184196;
		memory[648] = 4026531840;
		memory[649] = 4026531840;
		memory[650] = 4026531840;
		memory[651] = 99614850;
		memory[652] = 1879048800;
		memory[653] = 305135619;
		memory[654] = 4026531840;
		memory[655] = 4026531840;
		memory[656] = 4026531840;
		memory[657] = 99614816;
		memory[658] = 1879048799;
		memory[659] = 1610612776;

	//Программа фильтрации
		memory[700] = 1350565891;
		memory[701] = 1351614467;
		memory[702] = 1348468745;
		memory[703] = 1349517321;
		memory[704] = 4026531840;
		memory[705] = 446693384;
		memory[706] = 447741961;
		memory[707] = 4026531840;
		memory[708] = 4026531840;
		memory[709] = 4026531840;
		memory[710] = 79692102;
		memory[711] = 80740711;
		memory[712] = 115343625;
		memory[713] = 1357908920;
		memory[714] = 1363152000;
		memory[715] = 1372589384; 
		memory[716] = 4026531840;
		memory[717] = 450887694;
		memory[718] = 1090519050;
		memory[719] = 1091567627;
		memory[720] = 1361051648;
		memory[721] = 1362100224;
		memory[722] = 4026531840;
		memory[723] = 4026531840;
		memory[724] = 4026531840;
		memory[725] = 55575058;
		memory[726] = 56623667;
		memory[727] = 124781129;
		memory[728] = 4026531840;
		memory[729] = 4026531840;
		memory[730] = 89129301;
		memory[731] = 90177910;
		memory[732] = 57672435;
		memory[733] = 4026531840;
		memory[734] = 4026531840;
		memory[735] = 122684071;
		memory[736] = 56623823;
		memory[737] = 57672436;
		memory[738] = 4026531840;
		memory[739] = 4026531840;
		memory[740] = 4026531840;
		memory[741] = 55575222;
		memory[742] = 4026531840;
		memory[743] = 4026531840;
		memory[744] = 4026531840;
		memory[745] = 4026531840;
		memory[746] = 562036757;
		memory[747] = 4026531840;
		memory[748] = 4026531840;
		memory[749] = 4026531840;
		memory[750] = 4026531840;
		memory[751] = 805307159;
		memory[752] = 321912851;
		memory[753] = 4026531840;
		memory[754] = 4026531840;
		memory[755] = 4026531840;
		memory[756] = 99615337;
		memory[757] = 1879048917;
		memory[758] = 320864274;
		memory[759] = 4026531840;
		memory[760] = 4026531840;
		memory[761] = 4026531840;
		memory[762] = 99615304;
		memory[763] = 1879048913;
		memory[764] = 4026531840;
		memory[765] = 1610612776;
		memory[766] = 4026531840;
		memory[767] = 1610613236;
		memory[768] = 4026531840;
		memory[769] = 1610612796;
		memory[770] = 4026531840;
		memory[771] = 126878215;
		memory[772] = 61866929;
		memory[773] = 60818062;
		memory[774] = 4026531840;
		memory[775] = 4026531840;
		memory[776] = 4026531840;
		memory[777] = 59769659;
		memory[778] = 566231066;
		memory[779] = 4026531840;
		memory[780] = 4026531840;
		memory[781] = 4026531840;
		memory[782] = 4026531840;
		memory[783] = 805307289;
		memory[784] = 319815697;
		memory[785] = 4026531840;
		memory[786] = 4026531840;
		memory[787] = 4026531840;
		memory[788] = 4026531840;
		memory[789] = 99615277;
		memory[790] = 1879048912;
		memory[791] = 318767120;
		memory[792] = 4026531840;
		memory[793] = 4026531840;
		memory[794] = 4026531840;
		memory[795] = 99615244;
		memory[796] = 1879048911;
		memory[797] = 1610612816;
		memory[798] = 3221225472;
	
		//Массив q
		memory[2000] = 0;
		memory[2001] = 0;
		memory[2002] = 0;
		memory[2003] = 0;
		memory[2004] = 0;
		memory[2005] = 0;
		memory[2006] = 0;
		memory[2007] = 0;
		memory[2008] = 0;
		memory[2009] = 0;
		memory[2010] = 0;
		memory[2011] = 0;
		memory[2012] = 0;
		memory[2013] = 0;
		memory[2014] = 0;
		memory[2015] = 0;
		memory[2016] = 0;
		memory[2017] = 0;
		memory[2018] = 0;
		memory[2019] = 0;

		//Массив a
		memory[2200] = 0;
		memory[2201] = 1;
		memory[2202] = 2;
		memory[2203] = 3;
		memory[2204] = 4;
		memory[2205] = 5;
		memory[2206] = 6;
		memory[2207] = 7;
		memory[2208] = 8;
		memory[2209] = 9;
		memory[2210] = 10;
		memory[2211] = 11;
		memory[2212] = 12;
		memory[2213] = 13;
		memory[2214] = 14;
		memory[2215] = 15;
		memory[2216] = 16;
		memory[2217] = 17;
		memory[2218] = 18;
		memory[2219] = 19;
		memory[2220] = 20;
		memory[2221] = 21;
		memory[2222] = 22;
		memory[2223] = 23;
		memory[2224] = 24;
		memory[2225] = 25;
		memory[2226] = 26;
		memory[2227] = 27;
		memory[2228] = 28;
		memory[2229] = 29;
		memory[2230] = 30;
		memory[2231] = 31;
		memory[2232] = 32;
		memory[2233] = 33;
		memory[2234] = 34;
		memory[2235] = 35;
		memory[2236] = 36;
		memory[2237] = 37;
		memory[2238] = 38;
		memory[2239] = 39;
		memory[2240] = 40;
		memory[2241] = 41;
		memory[2242] = 42;
		memory[2243] = 43;
		memory[2244] = 44;
		memory[2245] = 45;
		memory[2246] = 46;
		memory[2247] = 47;
		memory[2248] = 48;
		memory[2249] = 49;

		//Массив b
		memory[2400] = 0;
		memory[2401] = 1;
		memory[2402] = 2;
		memory[2403] = 3;
		memory[2404] = 4;
		memory[2405] = 5;
		memory[2406] = 6;
		memory[2407] = 7;
		memory[2408] = 8;
		memory[2409] = 9;
		memory[2410] = 10;
		memory[2411] = 11;
		memory[2412] = 12;
		memory[2413] = 13;
		memory[2414] = 14;
		memory[2415] = 15;
		memory[2416] = 16;
		memory[2417] = 17;
		memory[2418] = 18;
		memory[2419] = 19;
		memory[2420] = 20;
		memory[2421] = 21;
		memory[2422] = 22;
		memory[2423] = 23;
		memory[2424] = 24;
		memory[2425] = 25;
		memory[2426] = 26;
		memory[2427] = 27;
		memory[2428] = 28;
		memory[2429] = 29;
		memory[2430] = 30;
		memory[2431] = 31;
		memory[2432] = 32;
		memory[2433] = 33;
		memory[2434] = 34;
		memory[2435] = 35;
		memory[2436] = 36;
		memory[2437] = 37;
		memory[2438] = 38;
		memory[2439] = 39;

		//массив для фильтрации
		memory[3000] = 0;
		memory[3001] = 10;
		memory[3002] = 20;
		memory[3003] = 3;
		memory[3004] = 4;
		memory[3005] = 5;
		memory[3006] = 6;
		memory[3007] = 7;
		memory[3008] = 8;
		memory[3009] = 90;
		memory[3010] = 10;
		memory[3011] = 11;
		memory[3012] = 12;
		memory[3013] = 13;
		memory[3014] = 14;
		memory[3015] = 15;
		memory[3016] = 16;
		memory[3017] = 17;
		memory[3018] = 18;
		memory[3019] = 19;
		memory[3020] = 20;
		memory[3021] = 21;
		memory[3022] = 22;
		memory[3023] = 23;
		memory[3024] = 24;
		memory[3025] = 25;
		memory[3026] = 26;
		memory[3027] = 27;
		memory[3028] = 28;
		memory[3029] = 29;
		memory[3030] = 30;
		memory[3031] = 31;
		memory[3032] = 32;
		memory[3033] = 33;
		memory[3034] = 34;
		memory[3035] = 35;
		memory[3036] = 36;
		memory[3037] = 37;
		memory[3038] = 38;
		memory[3039] = 39;
		memory[3040] = 40;
		memory[3041] = 41;
		memory[3042] = 42;
		memory[3043] = 43;
		memory[3044] = 44;
		memory[3045] = 45;
		memory[3046] = 46;
		memory[3047] = 47;
		memory[3048] = 48;
		memory[3049] = 49;
		memory[3050] = 50;
		memory[3051] = 51;
		memory[3052] = 52;
		memory[3053] = 53;
		memory[3054] = 54;
		memory[3055] = 55;
		memory[3056] = 56;
		memory[3057] = 57;
		memory[3058] = 58;
		memory[3059] = 59;
		memory[3060] = 60;
		memory[3061] = 61;
		memory[3062] = 62;
		memory[3063] = 63;
		memory[3064] = 64;
		memory[3065] = 65;
		memory[3066] = 66;
		memory[3067] = 67;
		memory[3068] = 68;
		memory[3069] = 69;
		memory[3070] = 70;
		memory[3071] = 71;
		memory[3072] = 72;
		memory[3073] = 73;
		memory[3074] = 74;
		memory[3075] = 75;
		memory[3076] = 76;
		memory[3077] = 77;
		memory[3078] = 78;
		memory[3079] = 79;
		memory[3080] = 80;
		memory[3081] = 81;
		memory[3082] = 0;
		memory[3083] = 0;
		memory[3084] = 0;
		memory[3085] = 0;
		memory[3086] = 0;
		memory[3087] = 0;
		memory[3088] = 0;
		memory[3089] = 0;

        cout << "RAM is now created..." << endl;

		SC_CTHREAD(ram_action_1, clock.pos());
        reset_signal_is(reset, true);   

		SC_CTHREAD(ram_action_2, clock.pos());
        reset_signal_is(reset, true);  
    }
};