// Workshop 6_1: Portfolio trading ///////////////////

function tradeCounterTrend()
{
	/*
	
	TimeFrame = 1;
	
	vars Price = series(price());
	vars Filtered = series(BandPass(Price,optimize(30,25,35),0.5));
	vars Signal = series(Fisher(Filtered,500));
	var Threshold = optimize(1,0.5,1.5,0.1);
	
	Stop = optimize(4,2,10) * ATR(100);
	Trail = 4*ATR(100);
	
	if(crossUnder(Signal,-Threshold)) {
		enterLong(100); 
		plot("Valley",*Signal,TRIANGLE,GREEN);
	}
	else if(crossOver(Signal,Threshold)) {
		enterShort(100);
		plot("Peak",*Signal,TRIANGLE,RED);
	}
	
	plot("Filtered",*Filtered,NEW,BLACK);
	plot("Signal",*Signal,NEW,BLACK);	
	
	*/
	
}

function tradeTrend()
{
	
	
	TimeFrame = 1;
	vars Price = series(price());
	vars Trend = series(LowPass(Price,optimize(500,300,700)));

	Stop = optimize(4,2,10) * ATR(100);
	Trail = 0;

	vars MMI_Raw = series(MMI(Price,300));
	vars MMI_Smooth = series(LowPass(MMI_Raw,500));
	
	if(falling(MMI_Smooth)) {
		if(valley(Trend)){
			enterLong(100);
			plot("Valley",*MMI_Smooth,TRIANGLE,GREEN);
		}
		else if(peak(Trend)){
			enterShort(100);
			plot("Peak",*MMI_Smooth,TRIANGLE,RED);
		}
	}
	
	//plot("Filtered",*Filtered,NEW,BLACK);
	plot("Signal",*MMI_Smooth,NEW,BLACK);	
	
	
}

function run()
{
	//if (Train) set(PARAMETERS+SKIP3);  			// generate and use optimized parameters
	//if (Test) set(PARAMETERS+SKIP1+SKIP2);  	// generate and use optimized parameters
	
	set(PARAMETERS+PRELOAD);
	setf(PlotMode,PL_ALL+PL_FINE+PL_FILE);
	set(PLOTNOW);
	
	//DataSplit = 75;

	PlotScale = 8;
	PlotWidth = 2000;
	PlotHeight1 = 700;
	PlotHeight2 = 200;
	
	NumCores = 2;										// use multiple cores (Zorro S only) all my cores !
	BarPeriod = 1;									// 1 minute bars
	LookBack = 2000;									// needed for Fisher()
	StartDate = 2018;
	EndDate = 2018; 									// fixed simulation period
	NumWFOCycles = 10; 								// activate WFO
	NumSampleCycles = 4;
	
	if(ReTrain) {
		UpdateDays = -1;								// update price data from the server 
		SelectWFO = -1;								// select the last cycle for re-optimization
	}
	
// portfolio loop

	while(asset(loop("AAPL")))
	while(algo(loop("TRND","CNTR")))
	{
		if(Algo == "TRND") 
			tradeTrend();
		else if(Algo == "CNTR") 
			tradeCounterTrend();
	}
	

	set(TESTNOW+LOGFILE);
}