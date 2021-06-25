<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_B43_PHY_LP_H_
#घोषणा LINUX_B43_PHY_LP_H_

/* Definitions क्रम the LP-PHY */


/* The CCK PHY रेजिस्टर range. */
#घोषणा B43_LPPHY_B_VERSION			B43_PHY_CCK(0x00) /* B PHY version */
#घोषणा B43_LPPHY_B_BBCONFIG			B43_PHY_CCK(0x01) /* B PHY BBConfig */
#घोषणा B43_LPPHY_B_RX_STAT0			B43_PHY_CCK(0x04) /* B PHY RX Status0 */
#घोषणा B43_LPPHY_B_RX_STAT1			B43_PHY_CCK(0x05) /* B PHY RX Status1 */
#घोषणा B43_LPPHY_B_CRS_THRESH			B43_PHY_CCK(0x06) /* B PHY CRS Thresh */
#घोषणा B43_LPPHY_B_TXERROR			B43_PHY_CCK(0x07) /* B PHY TxError */
#घोषणा B43_LPPHY_B_CHANNEL			B43_PHY_CCK(0x08) /* B PHY Channel */
#घोषणा B43_LPPHY_B_WORKAROUND			B43_PHY_CCK(0x09) /* B PHY workaround */
#घोषणा B43_LPPHY_B_TEST			B43_PHY_CCK(0x0A) /* B PHY Test */
#घोषणा B43_LPPHY_B_FOURWIRE_ADDR		B43_PHY_CCK(0x0B) /* B PHY Fourwire Address */
#घोषणा B43_LPPHY_B_FOURWIRE_DATA_HI		B43_PHY_CCK(0x0C) /* B PHY Fourwire Data Hi */
#घोषणा B43_LPPHY_B_FOURWIRE_DATA_LO		B43_PHY_CCK(0x0D) /* B PHY Fourwire Data Lo */
#घोषणा B43_LPPHY_B_BIST_STAT			B43_PHY_CCK(0x0E) /* B PHY Bist Status */
#घोषणा B43_LPPHY_PA_RAMP_TX_TO			B43_PHY_CCK(0x10) /* PA Ramp TX Timeout */
#घोषणा B43_LPPHY_RF_SYNTH_DC_TIMER		B43_PHY_CCK(0x11) /* RF Synth DC Timer */
#घोषणा B43_LPPHY_PA_RAMP_TX_TIME_IN		B43_PHY_CCK(0x12) /* PA ramp TX Time in */
#घोषणा B43_LPPHY_RX_FILTER_TIME_IN		B43_PHY_CCK(0x13) /* RX Filter Time in */
#घोषणा B43_LPPHY_PLL_COEFF_S			B43_PHY_CCK(0x18) /* PLL Coefficient(s) */
#घोषणा B43_LPPHY_PLL_OUT			B43_PHY_CCK(0x19) /* PLL Out */
#घोषणा B43_LPPHY_RSSI_THRES			B43_PHY_CCK(0x20) /* RSSI Threshold */
#घोषणा B43_LPPHY_IQ_THRES_HH			B43_PHY_CCK(0x21) /* IQ Threshold HH */
#घोषणा B43_LPPHY_IQ_THRES_H			B43_PHY_CCK(0x22) /* IQ Threshold H */
#घोषणा B43_LPPHY_IQ_THRES_L			B43_PHY_CCK(0x23) /* IQ Threshold L */
#घोषणा B43_LPPHY_IQ_THRES_LL			B43_PHY_CCK(0x24) /* IQ Threshold LL */
#घोषणा B43_LPPHY_AGC_GAIN			B43_PHY_CCK(0x25) /* AGC Gain */
#घोषणा B43_LPPHY_LNA_GAIN_RANGE		B43_PHY_CCK(0x26) /* LNA Gain Range */
#घोषणा B43_LPPHY_JSSI				B43_PHY_CCK(0x27) /* JSSI */
#घोषणा B43_LPPHY_TSSI_CTL			B43_PHY_CCK(0x28) /* TSSI Control */
#घोषणा B43_LPPHY_TSSI				B43_PHY_CCK(0x29) /* TSSI */
#घोषणा B43_LPPHY_TR_LOSS			B43_PHY_CCK(0x2A) /* TR Loss */
#घोषणा B43_LPPHY_LO_LEAKAGE			B43_PHY_CCK(0x2B) /* LO Leakage */
#घोषणा B43_LPPHY_LO_RSSIACC			B43_PHY_CCK(0x2C) /* LO RSSIAcc */
#घोषणा B43_LPPHY_LO_IQ_MAG_ACC			B43_PHY_CCK(0x2D) /* LO IQ Mag Acc */
#घोषणा B43_LPPHY_TX_DCOFFSET1			B43_PHY_CCK(0x2E) /* TX DCOffset1 */
#घोषणा B43_LPPHY_TX_DCOFFSET2			B43_PHY_CCK(0x2F) /* TX DCOffset2 */
#घोषणा B43_LPPHY_SYNCPEAKCNT			B43_PHY_CCK(0x30) /* SyncPeakCnt */
#घोषणा B43_LPPHY_SYNCFREQ			B43_PHY_CCK(0x31) /* SyncFreq */
#घोषणा B43_LPPHY_SYNCDIVERSITYCTL		B43_PHY_CCK(0x32) /* SyncDiversityControl */
#घोषणा B43_LPPHY_PEAKENERGYL			B43_PHY_CCK(0x33) /* PeakEnergyL */
#घोषणा B43_LPPHY_PEAKENERGYH			B43_PHY_CCK(0x34) /* PeakEnergyH */
#घोषणा B43_LPPHY_SYNCCTL			B43_PHY_CCK(0x35) /* SyncControl */
#घोषणा B43_LPPHY_DSSSSTEP			B43_PHY_CCK(0x38) /* DsssStep */
#घोषणा B43_LPPHY_DSSSWARMUP			B43_PHY_CCK(0x39) /* DsssWarmup */
#घोषणा B43_LPPHY_DSSSSIGPOW			B43_PHY_CCK(0x3D) /* DsssSigPow */
#घोषणा B43_LPPHY_SFDDETECTBLOCKTIME		B43_PHY_CCK(0x40) /* SfdDetectBlockTIme */
#घोषणा B43_LPPHY_SFDTO				B43_PHY_CCK(0x41) /* SFDTimeOut */
#घोषणा B43_LPPHY_SFDCTL			B43_PHY_CCK(0x42) /* SFDControl */
#घोषणा B43_LPPHY_RXDBG				B43_PHY_CCK(0x43) /* rxDebug */
#घोषणा B43_LPPHY_RX_DELAYCOMP			B43_PHY_CCK(0x44) /* RX DelayComp */
#घोषणा B43_LPPHY_CRSDROPOUTTO			B43_PHY_CCK(0x45) /* CRSDropoutTimeout */
#घोषणा B43_LPPHY_PSEUDOSHORTTO			B43_PHY_CCK(0x46) /* PseuकरोShortTimeout */
#घोषणा B43_LPPHY_PR3931			B43_PHY_CCK(0x47) /* PR3931 */
#घोषणा B43_LPPHY_DSSSCOEFF1			B43_PHY_CCK(0x48) /* DSSSCoeff1 */
#घोषणा B43_LPPHY_DSSSCOEFF2			B43_PHY_CCK(0x49) /* DSSSCoeff2 */
#घोषणा B43_LPPHY_CCKCOEFF1			B43_PHY_CCK(0x4A) /* CCKCoeff1 */
#घोषणा B43_LPPHY_CCKCOEFF2			B43_PHY_CCK(0x4B) /* CCKCoeff2 */
#घोषणा B43_LPPHY_TRCORR			B43_PHY_CCK(0x4C) /* TRCorr */
#घोषणा B43_LPPHY_ANGLESCALE			B43_PHY_CCK(0x4D) /* AngleScale */
#घोषणा B43_LPPHY_OPTIONALMODES2		B43_PHY_CCK(0x4F) /* OptionalModes2 */
#घोषणा B43_LPPHY_CCKLMSSTEPSIZE		B43_PHY_CCK(0x50) /* CCKLMSStepSize */
#घोषणा B43_LPPHY_DFEBYPASS			B43_PHY_CCK(0x51) /* DFEBypass */
#घोषणा B43_LPPHY_CCKSTARTDELAYLONG		B43_PHY_CCK(0x52) /* CCKStartDelayLong */
#घोषणा B43_LPPHY_CCKSTARTDELAYSHORT		B43_PHY_CCK(0x53) /* CCKStartDelayShort */
#घोषणा B43_LPPHY_PPROCCHDELAY			B43_PHY_CCK(0x54) /* PprocChDelay */
#घोषणा B43_LPPHY_PPROCONOFF			B43_PHY_CCK(0x55) /* PProcOnOff */
#घोषणा B43_LPPHY_LNAGAINTWOBIT10		B43_PHY_CCK(0x5B) /* LNAGainTwoBit10 */
#घोषणा B43_LPPHY_LNAGAINTWOBIT32		B43_PHY_CCK(0x5C) /* LNAGainTwoBit32 */
#घोषणा B43_LPPHY_OPTIONALMODES			B43_PHY_CCK(0x5D) /* OptionalModes */
#घोषणा B43_LPPHY_B_RX_STAT2			B43_PHY_CCK(0x5E) /* B PHY RX Status2 */
#घोषणा B43_LPPHY_B_RX_STAT3			B43_PHY_CCK(0x5F) /* B PHY RX Status3 */
#घोषणा B43_LPPHY_PWDNDACDELAY			B43_PHY_CCK(0x63) /* pwdnDacDelay */
#घोषणा B43_LPPHY_FINEDIGIGAIN_CTL		B43_PHY_CCK(0x67) /* FineDigiGain Control */
#घोषणा B43_LPPHY_LG2GAINTBLLNA8		B43_PHY_CCK(0x68) /* Lg2GainTblLNA8 */
#घोषणा B43_LPPHY_LG2GAINTBLLNA28		B43_PHY_CCK(0x69) /* Lg2GainTblLNA28 */
#घोषणा B43_LPPHY_GAINTBLLNATRSW		B43_PHY_CCK(0x6A) /* GainTblLNATrSw */
#घोषणा B43_LPPHY_PEAKENERGY			B43_PHY_CCK(0x6B) /* PeakEnergy */
#घोषणा B43_LPPHY_LG2INITGAIN			B43_PHY_CCK(0x6C) /* lg2InitGain */
#घोषणा B43_LPPHY_BLANKCOUNTLNAPGA		B43_PHY_CCK(0x6D) /* BlankCountLnaPga */
#घोषणा B43_LPPHY_LNAGAINTWOBIT54		B43_PHY_CCK(0x6E) /* LNAGainTwoBit54 */
#घोषणा B43_LPPHY_LNAGAINTWOBIT76		B43_PHY_CCK(0x6F) /* LNAGainTwoBit76 */
#घोषणा B43_LPPHY_JSSICTL			B43_PHY_CCK(0x70) /* JSSIControl */
#घोषणा B43_LPPHY_LG2GAINTBLLNA44		B43_PHY_CCK(0x71) /* Lg2GainTblLNA44 */
#घोषणा B43_LPPHY_LG2GAINTBLLNA62		B43_PHY_CCK(0x72) /* Lg2GainTblLNA62 */

/* The OFDM PHY रेजिस्टर range. */
#घोषणा B43_LPPHY_VERSION			B43_PHY_OFDM(0x00) /* Version */
#घोषणा B43_LPPHY_BBCONFIG			B43_PHY_OFDM(0x01) /* BBConfig */
#घोषणा B43_LPPHY_RX_STAT0			B43_PHY_OFDM(0x04) /* RX Status0 */
#घोषणा B43_LPPHY_RX_STAT1			B43_PHY_OFDM(0x05) /* RX Status1 */
#घोषणा B43_LPPHY_TX_ERROR			B43_PHY_OFDM(0x07) /* TX Error */
#घोषणा B43_LPPHY_CHANNEL			B43_PHY_OFDM(0x08) /* Channel */
#घोषणा B43_LPPHY_WORKAROUND			B43_PHY_OFDM(0x09) /* workaround */
#घोषणा B43_LPPHY_FOURWIRE_ADDR			B43_PHY_OFDM(0x0B) /* Fourwire Address */
#घोषणा B43_LPPHY_FOURWIREDATAHI		B43_PHY_OFDM(0x0C) /* FourwireDataHi */
#घोषणा B43_LPPHY_FOURWIREDATALO		B43_PHY_OFDM(0x0D) /* FourwireDataLo */
#घोषणा B43_LPPHY_BISTSTAT0			B43_PHY_OFDM(0x0E) /* BistStatus0 */
#घोषणा B43_LPPHY_BISTSTAT1			B43_PHY_OFDM(0x0F) /* BistStatus1 */
#घोषणा B43_LPPHY_CRSGAIN_CTL			B43_PHY_OFDM(0x10) /* crsgain Control */
#घोषणा B43_LPPHY_OFDMPWR_THRESH0		B43_PHY_OFDM(0x11) /* ofdmPower Thresh0 */
#घोषणा B43_LPPHY_OFDMPWR_THRESH1		B43_PHY_OFDM(0x12) /* ofdmPower Thresh1 */
#घोषणा B43_LPPHY_OFDMPWR_THRESH2		B43_PHY_OFDM(0x13) /* ofdmPower Thresh2 */
#घोषणा B43_LPPHY_DSSSPWR_THRESH0		B43_PHY_OFDM(0x14) /* dsssPower Thresh0 */
#घोषणा B43_LPPHY_DSSSPWR_THRESH1		B43_PHY_OFDM(0x15) /* dsssPower Thresh1 */
#घोषणा B43_LPPHY_MINPWR_LEVEL			B43_PHY_OFDM(0x16) /* MinPower Level */
#घोषणा B43_LPPHY_OFDMSYNCTHRESH0		B43_PHY_OFDM(0x17) /* ofdmSyncThresh0 */
#घोषणा B43_LPPHY_OFDMSYNCTHRESH1		B43_PHY_OFDM(0x18) /* ofdmSyncThresh1 */
#घोषणा B43_LPPHY_FINEFREQEST			B43_PHY_OFDM(0x19) /* FineFreqEst */
#घोषणा B43_LPPHY_IDLEAFTERPKTRXTO		B43_PHY_OFDM(0x1A) /* IDLEafterPktRXTimeout */
#घोषणा B43_LPPHY_LTRN_CTL			B43_PHY_OFDM(0x1B) /* LTRN Control */
#घोषणा B43_LPPHY_DCOFFSETTRANSIENT		B43_PHY_OFDM(0x1C) /* DCOffsetTransient */
#घोषणा B43_LPPHY_PREAMBLEINTO			B43_PHY_OFDM(0x1D) /* PreambleInTimeout */
#घोषणा B43_LPPHY_PREAMBLECONFIRMTO		B43_PHY_OFDM(0x1E) /* PreambleConfirmTimeout */
#घोषणा B43_LPPHY_CLIPTHRESH			B43_PHY_OFDM(0x1F) /* ClipThresh */
#घोषणा B43_LPPHY_CLIPCTRTHRESH			B43_PHY_OFDM(0x20) /* ClipCtrThresh */
#घोषणा B43_LPPHY_OFDMSYNCTIMER_CTL		B43_PHY_OFDM(0x21) /* ofdmSyncTimer Control */
#घोषणा B43_LPPHY_WAITFORPHYSELTO		B43_PHY_OFDM(0x22) /* Waitक्रमPHYSelTimeout */
#घोषणा B43_LPPHY_HIGAINDB			B43_PHY_OFDM(0x23) /* HiGainDB */
#घोषणा B43_LPPHY_LOWGAINDB			B43_PHY_OFDM(0x24) /* LowGainDB */
#घोषणा B43_LPPHY_VERYLOWGAINDB			B43_PHY_OFDM(0x25) /* VeryLowGainDB */
#घोषणा B43_LPPHY_GAINMISMATCH			B43_PHY_OFDM(0x26) /* gainMismatch */
#घोषणा B43_LPPHY_GAINसूचीECTMISMATCH		B43_PHY_OFDM(0x27) /* gaindirectMismatch */
#घोषणा B43_LPPHY_PWR_THRESH0			B43_PHY_OFDM(0x28) /* Power Thresh0 */
#घोषणा B43_LPPHY_PWR_THRESH1			B43_PHY_OFDM(0x29) /* Power Thresh1 */
#घोषणा B43_LPPHY_DETECTOR_DELAY_ADJUST		B43_PHY_OFDM(0x2A) /* Detector Delay Adjust */
#घोषणा B43_LPPHY_REDUCED_DETECTOR_DELAY	B43_PHY_OFDM(0x2B) /* Reduced Detector Delay */
#घोषणा B43_LPPHY_DATA_TO			B43_PHY_OFDM(0x2C) /* data Timeout */
#घोषणा B43_LPPHY_CORRELATOR_DIS_DELAY		B43_PHY_OFDM(0x2D) /* correlator Dis Delay */
#घोषणा B43_LPPHY_DIVERSITY_GAINBACK		B43_PHY_OFDM(0x2E) /* Diversity GainBack */
#घोषणा B43_LPPHY_DSSS_CONFIRM_CNT		B43_PHY_OFDM(0x2F) /* DSSS Confirm Cnt */
#घोषणा B43_LPPHY_DC_BLANK_INT			B43_PHY_OFDM(0x30) /* DC Blank Interval */
#घोषणा B43_LPPHY_GAIN_MISMATCH_LIMIT		B43_PHY_OFDM(0x31) /* gain Mismatch Limit */
#घोषणा B43_LPPHY_CRS_ED_THRESH			B43_PHY_OFDM(0x32) /* crs ed thresh */
#घोषणा B43_LPPHY_PHASE_SHIFT_CTL		B43_PHY_OFDM(0x33) /* phase shअगरt Control */
#घोषणा B43_LPPHY_INPUT_PWRDB			B43_PHY_OFDM(0x34) /* Input PowerDB */
#घोषणा B43_LPPHY_OFDM_SYNC_CTL			B43_PHY_OFDM(0x35) /* ofdm sync Control */
#घोषणा B43_LPPHY_AFE_ADC_CTL_0			B43_PHY_OFDM(0x36) /* Afe ADC Control 0 */
#घोषणा B43_LPPHY_AFE_ADC_CTL_1			B43_PHY_OFDM(0x37) /* Afe ADC Control 1 */
#घोषणा B43_LPPHY_AFE_ADC_CTL_2			B43_PHY_OFDM(0x38) /* Afe ADC Control 2 */
#घोषणा B43_LPPHY_AFE_DAC_CTL			B43_PHY_OFDM(0x39) /* Afe DAC Control */
#घोषणा B43_LPPHY_AFE_CTL			B43_PHY_OFDM(0x3A) /* Afe Control */
#घोषणा B43_LPPHY_AFE_CTL_OVR			B43_PHY_OFDM(0x3B) /* Afe Control Ovr */
#घोषणा B43_LPPHY_AFE_CTL_OVRVAL		B43_PHY_OFDM(0x3C) /* Afe Control OvrVal */
#घोषणा B43_LPPHY_AFE_RSSI_CTL_0		B43_PHY_OFDM(0x3D) /* Afe RSSI Control 0 */
#घोषणा B43_LPPHY_AFE_RSSI_CTL_1		B43_PHY_OFDM(0x3E) /* Afe RSSI Control 1 */
#घोषणा B43_LPPHY_AFE_RSSI_SEL			B43_PHY_OFDM(0x3F) /* Afe RSSI Sel */
#घोषणा B43_LPPHY_RADAR_THRESH			B43_PHY_OFDM(0x40) /* Radar Thresh */
#घोषणा B43_LPPHY_RADAR_BLANK_INT		B43_PHY_OFDM(0x41) /* Radar blank Interval */
#घोषणा B43_LPPHY_RADAR_MIN_FM_INT		B43_PHY_OFDM(0x42) /* Radar min fm Interval */
#घोषणा B43_LPPHY_RADAR_GAIN_TO			B43_PHY_OFDM(0x43) /* Radar gain समयout */
#घोषणा B43_LPPHY_RADAR_PULSE_TO		B43_PHY_OFDM(0x44) /* Radar pulse समयout */
#घोषणा B43_LPPHY_RADAR_DETECT_FM_CTL		B43_PHY_OFDM(0x45) /* Radar detect FM Control */
#घोषणा B43_LPPHY_RADAR_DETECT_EN		B43_PHY_OFDM(0x46) /* Radar detect En */
#घोषणा B43_LPPHY_RADAR_RD_DATA_REG		B43_PHY_OFDM(0x47) /* Radar Rd Data Reg */
#घोषणा B43_LPPHY_LP_PHY_CTL			B43_PHY_OFDM(0x48) /* LP PHY Control */
#घोषणा B43_LPPHY_CLASSIFIER_CTL		B43_PHY_OFDM(0x49) /* classअगरier Control */
#घोषणा B43_LPPHY_RESET_CTL			B43_PHY_OFDM(0x4A) /* reset Control */
#घोषणा B43_LPPHY_CLKEN_CTL			B43_PHY_OFDM(0x4B) /* ClkEn Control */
#घोषणा B43_LPPHY_RF_OVERRIDE_0			B43_PHY_OFDM(0x4C) /* RF Override 0 */
#घोषणा B43_LPPHY_RF_OVERRIDE_VAL_0		B43_PHY_OFDM(0x4D) /* RF Override Val 0 */
#घोषणा B43_LPPHY_TR_LOOKUP_1			B43_PHY_OFDM(0x4E) /* TR Lookup 1 */
#घोषणा B43_LPPHY_TR_LOOKUP_2			B43_PHY_OFDM(0x4F) /* TR Lookup 2 */
#घोषणा B43_LPPHY_RSSISELLOOKUP1		B43_PHY_OFDM(0x50) /* RssiSelLookup1 */
#घोषणा B43_LPPHY_IQLO_CAL_CMD			B43_PHY_OFDM(0x51) /* iqlo Cal Cmd */
#घोषणा B43_LPPHY_IQLO_CAL_CMD_N_NUM		B43_PHY_OFDM(0x52) /* iqlo Cal Cmd N num */
#घोषणा B43_LPPHY_IQLO_CAL_CMD_G_CTL		B43_PHY_OFDM(0x53) /* iqlo Cal Cmd G control */
#घोषणा B43_LPPHY_MACINT_DBG_REGISTER		B43_PHY_OFDM(0x54) /* macपूर्णांक Debug Register */
#घोषणा B43_LPPHY_TABLE_ADDR			B43_PHY_OFDM(0x55) /* Table Address */
#घोषणा B43_LPPHY_TABLEDATALO			B43_PHY_OFDM(0x56) /* TabledataLo */
#घोषणा B43_LPPHY_TABLEDATAHI			B43_PHY_OFDM(0x57) /* TabledataHi */
#घोषणा B43_LPPHY_PHY_CRS_ENABLE_ADDR		B43_PHY_OFDM(0x58) /* phy CRS Enable Address */
#घोषणा B43_LPPHY_IDLETIME_CTL			B43_PHY_OFDM(0x59) /* Idleसमय Control */
#घोषणा B43_LPPHY_IDLETIME_CRS_ON_LO		B43_PHY_OFDM(0x5A) /* Idleसमय CRS On Lo */
#घोषणा B43_LPPHY_IDLETIME_CRS_ON_HI		B43_PHY_OFDM(0x5B) /* Idleसमय CRS On Hi */
#घोषणा B43_LPPHY_IDLETIME_MEAS_TIME_LO		B43_PHY_OFDM(0x5C) /* Idleसमय Meas Time Lo */
#घोषणा B43_LPPHY_IDLETIME_MEAS_TIME_HI		B43_PHY_OFDM(0x5D) /* Idleसमय Meas Time Hi */
#घोषणा B43_LPPHY_RESET_LEN_OFDM_TX_ADDR	B43_PHY_OFDM(0x5E) /* Reset len Ofdm TX Address */
#घोषणा B43_LPPHY_RESET_LEN_OFDM_RX_ADDR	B43_PHY_OFDM(0x5F) /* Reset len Ofdm RX Address */
#घोषणा B43_LPPHY_REG_CRS_ENABLE		B43_PHY_OFDM(0x60) /* reg crs enable */
#घोषणा B43_LPPHY_PLCP_TMT_STR0_CTR_MIN		B43_PHY_OFDM(0x61) /* PLCP Tmt Str0 Ctr Min */
#घोषणा B43_LPPHY_PKT_FSM_RESET_LEN_VAL		B43_PHY_OFDM(0x62) /* Pkt fsm Reset Len Value */
#घोषणा B43_LPPHY_READSYM2RESET_CTL		B43_PHY_OFDM(0x63) /* पढ़ोsym2reset Control */
#घोषणा B43_LPPHY_DC_FILTER_DELAY1		B43_PHY_OFDM(0x64) /* Dc filter delay1 */
#घोषणा B43_LPPHY_PACKET_RX_ACTIVE_TO		B43_PHY_OFDM(0x65) /* packet rx Active समयout */
#घोषणा B43_LPPHY_ED_TOVAL			B43_PHY_OFDM(0x66) /* ed समयoutValue */
#घोषणा B43_LPPHY_HOLD_CRS_ON_VAL		B43_PHY_OFDM(0x67) /* hold CRS On Value */
#घोषणा B43_LPPHY_OFDM_TX_PHY_CRS_DELAY_VAL	B43_PHY_OFDM(0x69) /* ofdm tx phy CRS Delay Value */
#घोषणा B43_LPPHY_CCK_TX_PHY_CRS_DELAY_VAL	B43_PHY_OFDM(0x6A) /* cck tx phy CRS Delay Value */
#घोषणा B43_LPPHY_ED_ON_CONFIRM_TIMER_VAL	B43_PHY_OFDM(0x6B) /* Ed on confirm Timer Value */
#घोषणा B43_LPPHY_ED_OFFSET_CONFIRM_TIMER_VAL	B43_PHY_OFDM(0x6C) /* Ed offset confirm Timer Value */
#घोषणा B43_LPPHY_PHY_CRS_OFFSET_TIMER_VAL	B43_PHY_OFDM(0x6D) /* phy CRS offset Timer Value */
#घोषणा B43_LPPHY_ADC_COMPENSATION_CTL		B43_PHY_OFDM(0x70) /* ADC Compensation Control */
#घोषणा B43_LPPHY_LOG2_RBPSK_ADDR		B43_PHY_OFDM(0x71) /* log2 RBPSK Address */
#घोषणा B43_LPPHY_LOG2_RQPSK_ADDR		B43_PHY_OFDM(0x72) /* log2 RQPSK Address */
#घोषणा B43_LPPHY_LOG2_R16QAM_ADDR		B43_PHY_OFDM(0x73) /* log2 R16QAM Address */
#घोषणा B43_LPPHY_LOG2_R64QAM_ADDR		B43_PHY_OFDM(0x74) /* log2 R64QAM Address */
#घोषणा B43_LPPHY_OFFSET_BPSK_ADDR		B43_PHY_OFDM(0x75) /* offset BPSK Address */
#घोषणा B43_LPPHY_OFFSET_QPSK_ADDR		B43_PHY_OFDM(0x76) /* offset QPSK Address */
#घोषणा B43_LPPHY_OFFSET_16QAM_ADDR		B43_PHY_OFDM(0x77) /* offset 16QAM Address */
#घोषणा B43_LPPHY_OFFSET_64QAM_ADDR		B43_PHY_OFDM(0x78) /* offset 64QAM Address */
#घोषणा B43_LPPHY_ALPHA1			B43_PHY_OFDM(0x79) /* Alpha1 */
#घोषणा B43_LPPHY_ALPHA2			B43_PHY_OFDM(0x7A) /* Alpha2 */
#घोषणा B43_LPPHY_BETA1				B43_PHY_OFDM(0x7B) /* Beta1 */
#घोषणा B43_LPPHY_BETA2				B43_PHY_OFDM(0x7C) /* Beta2 */
#घोषणा B43_LPPHY_LOOP_NUM_ADDR			B43_PHY_OFDM(0x7D) /* Loop Num Address */
#घोषणा B43_LPPHY_STR_COLLMAX_SMPL_ADDR		B43_PHY_OFDM(0x7E) /* Str Collmax Sample Address */
#घोषणा B43_LPPHY_MAX_SMPL_COARSE_FINE_ADDR	B43_PHY_OFDM(0x7F) /* Max Sample Coarse/Fine Address */
#घोषणा B43_LPPHY_MAX_SMPL_COARSE_STR0CTR_ADDR	B43_PHY_OFDM(0x80) /* Max Sample Coarse/Str0Ctr Address */
#घोषणा B43_LPPHY_IQ_ENABLE_WAIT_TIME_ADDR	B43_PHY_OFDM(0x81) /* IQ Enable Wait Time Address */
#घोषणा B43_LPPHY_IQ_NUM_SMPLS_ADDR		B43_PHY_OFDM(0x82) /* IQ Num Samples Address */
#घोषणा B43_LPPHY_IQ_ACC_HI_ADDR		B43_PHY_OFDM(0x83) /* IQ Acc Hi Address */
#घोषणा B43_LPPHY_IQ_ACC_LO_ADDR		B43_PHY_OFDM(0x84) /* IQ Acc Lo Address */
#घोषणा B43_LPPHY_IQ_I_PWR_ACC_HI_ADDR		B43_PHY_OFDM(0x85) /* IQ I PWR Acc Hi Address */
#घोषणा B43_LPPHY_IQ_I_PWR_ACC_LO_ADDR		B43_PHY_OFDM(0x86) /* IQ I PWR Acc Lo Address */
#घोषणा B43_LPPHY_IQ_Q_PWR_ACC_HI_ADDR		B43_PHY_OFDM(0x87) /* IQ Q PWR Acc Hi Address */
#घोषणा B43_LPPHY_IQ_Q_PWR_ACC_LO_ADDR		B43_PHY_OFDM(0x88) /* IQ Q PWR Acc Lo Address */
#घोषणा B43_LPPHY_MAXNUMSTEPS			B43_PHY_OFDM(0x89) /* MaxNumsteps */
#घोषणा B43_LPPHY_ROTORPHASE_ADDR		B43_PHY_OFDM(0x8A) /* RotorPhase Address */
#घोषणा B43_LPPHY_ADVANCEDRETARDROTOR_ADDR	B43_PHY_OFDM(0x8B) /* AdvancedRetardRotor Address */
#घोषणा B43_LPPHY_RSSIADCDELAY_CTL_ADDR		B43_PHY_OFDM(0x8D) /* rssiAdcdelay Control Address */
#घोषणा B43_LPPHY_TSSISTAT_ADDR			B43_PHY_OFDM(0x8E) /* tssiStatus Address */
#घोषणा B43_LPPHY_TEMPSENSESTAT_ADDR		B43_PHY_OFDM(0x8F) /* tempsenseStatus Address */
#घोषणा B43_LPPHY_TEMPSENSE_CTL_ADDR		B43_PHY_OFDM(0x90) /* tempsense Control Address */
#घोषणा B43_LPPHY_WRSSISTAT_ADDR		B43_PHY_OFDM(0x91) /* wrssistatus Address */
#घोषणा B43_LPPHY_MUFACTORADDR			B43_PHY_OFDM(0x92) /* mufactoraddr */
#घोषणा B43_LPPHY_SCRAMSTATE_ADDR		B43_PHY_OFDM(0x93) /* scramstate Address */
#घोषणा B43_LPPHY_TXHOLDOFFADDR			B43_PHY_OFDM(0x94) /* txholकरोffaddr */
#घोषणा B43_LPPHY_PKTGAINVAL_ADDR		B43_PHY_OFDM(0x95) /* pktgainval Address */
#घोषणा B43_LPPHY_COARSEESTIM_ADDR		B43_PHY_OFDM(0x96) /* Coarseestim Address */
#घोषणा B43_LPPHY_STATE_TRANSITION_ADDR		B43_PHY_OFDM(0x97) /* state Transition Address */
#घोषणा B43_LPPHY_TRN_OFFSET_ADDR		B43_PHY_OFDM(0x98) /* TRN offset Address */
#घोषणा B43_LPPHY_NUM_ROTOR_ADDR		B43_PHY_OFDM(0x99) /* Num Rotor Address */
#घोषणा B43_LPPHY_VITERBI_OFFSET_ADDR		B43_PHY_OFDM(0x9A) /* Viterbi Offset Address */
#घोषणा B43_LPPHY_SMPL_COLLECT_WAIT_ADDR	B43_PHY_OFDM(0x9B) /* Sample collect रुको Address */
#घोषणा B43_LPPHY_A_PHY_CTL_ADDR		B43_PHY_OFDM(0x9C) /* A PHY Control Address */
#घोषणा B43_LPPHY_NUM_PASS_THROUGH_ADDR		B43_PHY_OFDM(0x9D) /* Num Pass Through Address */
#घोषणा B43_LPPHY_RX_COMP_COEFF_S		B43_PHY_OFDM(0x9E) /* RX Comp coefficient(s) */
#घोषणा B43_LPPHY_CPAROTATEVAL			B43_PHY_OFDM(0x9F) /* cpaRotateValue */
#घोषणा B43_LPPHY_SMPL_PLAY_COUNT		B43_PHY_OFDM(0xA0) /* Sample play count */
#घोषणा B43_LPPHY_SMPL_PLAY_BUFFER_CTL		B43_PHY_OFDM(0xA1) /* Sample play Buffer Control */
#घोषणा B43_LPPHY_FOURWIRE_CTL			B43_PHY_OFDM(0xA2) /* fourwire Control */
#घोषणा B43_LPPHY_CPA_TAILCOUNT_VAL		B43_PHY_OFDM(0xA3) /* CPA TailCount Value */
#घोषणा B43_LPPHY_TX_PWR_CTL_CMD		B43_PHY_OFDM(0xA4) /* TX Power Control Cmd */
#घोषणा  B43_LPPHY_TX_PWR_CTL_CMD_MODE		0xE000 /* TX घातer control mode mask */
#घोषणा   B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF	0x0000 /* TX घातer control is OFF */
#घोषणा   B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW	0x8000 /* TX घातer control is SOFTWARE */
#घोषणा   B43_LPPHY_TX_PWR_CTL_CMD_MODE_HW	0xE000 /* TX घातer control is HARDWARE */
#घोषणा B43_LPPHY_TX_PWR_CTL_NNUM		B43_PHY_OFDM(0xA5) /* TX Power Control Nnum */
#घोषणा B43_LPPHY_TX_PWR_CTL_IDLETSSI		B43_PHY_OFDM(0xA6) /* TX Power Control IdleTssi */
#घोषणा B43_LPPHY_TX_PWR_CTL_TARGETPWR		B43_PHY_OFDM(0xA7) /* TX Power Control TargetPower */
#घोषणा B43_LPPHY_TX_PWR_CTL_DELTAPWR_LIMIT	B43_PHY_OFDM(0xA8) /* TX Power Control DeltaPower Limit */
#घोषणा B43_LPPHY_TX_PWR_CTL_BASEINDEX		B43_PHY_OFDM(0xA9) /* TX Power Control BaseIndex */
#घोषणा B43_LPPHY_TX_PWR_CTL_PWR_INDEX		B43_PHY_OFDM(0xAA) /* TX Power Control Power Index */
#घोषणा B43_LPPHY_TX_PWR_CTL_STAT		B43_PHY_OFDM(0xAB) /* TX Power Control Status */
#घोषणा B43_LPPHY_LP_RF_SIGNAL_LUT		B43_PHY_OFDM(0xAC) /* LP RF संकेत LUT */
#घोषणा B43_LPPHY_RX_RADIO_CTL_FILTER_STATE	B43_PHY_OFDM(0xAD) /* RX Radio Control Filter State */
#घोषणा B43_LPPHY_RX_RADIO_CTL			B43_PHY_OFDM(0xAE) /* RX Radio Control */
#घोषणा B43_LPPHY_NRSSI_STAT_ADDR		B43_PHY_OFDM(0xAF) /* NRSSI status Address */
#घोषणा B43_LPPHY_RF_OVERRIDE_2			B43_PHY_OFDM(0xB0) /* RF override 2 */
#घोषणा B43_LPPHY_RF_OVERRIDE_2_VAL		B43_PHY_OFDM(0xB1) /* RF override 2 val */
#घोषणा B43_LPPHY_PS_CTL_OVERRIDE_VAL0		B43_PHY_OFDM(0xB2) /* PS Control override val0 */
#घोषणा B43_LPPHY_PS_CTL_OVERRIDE_VAL1		B43_PHY_OFDM(0xB3) /* PS Control override val1 */
#घोषणा B43_LPPHY_PS_CTL_OVERRIDE_VAL2		B43_PHY_OFDM(0xB4) /* PS Control override val2 */
#घोषणा B43_LPPHY_TX_GAIN_CTL_OVERRIDE_VAL	B43_PHY_OFDM(0xB5) /* TX gain Control override val */
#घोषणा B43_LPPHY_RX_GAIN_CTL_OVERRIDE_VAL	B43_PHY_OFDM(0xB6) /* RX gain Control override val */
#घोषणा B43_LPPHY_AFE_DDFS			B43_PHY_OFDM(0xB7) /* AFE DDFS */
#घोषणा B43_LPPHY_AFE_DDFS_POINTER_INIT		B43_PHY_OFDM(0xB8) /* AFE DDFS poपूर्णांकer init */
#घोषणा B43_LPPHY_AFE_DDFS_INCR_INIT		B43_PHY_OFDM(0xB9) /* AFE DDFS incr init */
#घोषणा B43_LPPHY_MRCNOISEREDUCTION		B43_PHY_OFDM(0xBA) /* mrcNoiseReduction */
#घोषणा B43_LPPHY_TR_LOOKUP_3			B43_PHY_OFDM(0xBB) /* TR Lookup 3 */
#घोषणा B43_LPPHY_TR_LOOKUP_4			B43_PHY_OFDM(0xBC) /* TR Lookup 4 */
#घोषणा B43_LPPHY_RADAR_FIFO_STAT		B43_PHY_OFDM(0xBD) /* Radar FIFO Status */
#घोषणा B43_LPPHY_GPIO_OUTEN			B43_PHY_OFDM(0xBE) /* GPIO Out enable */
#घोषणा B43_LPPHY_GPIO_SELECT			B43_PHY_OFDM(0xBF) /* GPIO Select */
#घोषणा B43_LPPHY_GPIO_OUT			B43_PHY_OFDM(0xC0) /* GPIO Out */
#घोषणा B43_LPPHY_4C3				B43_PHY_OFDM(0xC3) /* unknown, used during BB init */
#घोषणा B43_LPPHY_4C4				B43_PHY_OFDM(0xC4) /* unknown, used during BB init */
#घोषणा B43_LPPHY_4C5				B43_PHY_OFDM(0xC5) /* unknown, used during BB init */
#घोषणा B43_LPPHY_TR_LOOKUP_5			B43_PHY_OFDM(0xC7) /* TR Lookup 5 */
#घोषणा B43_LPPHY_TR_LOOKUP_6			B43_PHY_OFDM(0xC8) /* TR Lookup 6 */
#घोषणा B43_LPPHY_TR_LOOKUP_7			B43_PHY_OFDM(0xC9) /* TR Lookup 7 */
#घोषणा B43_LPPHY_TR_LOOKUP_8			B43_PHY_OFDM(0xCA) /* TR Lookup 8 */
#घोषणा B43_LPPHY_RF_PWR_OVERRIDE		B43_PHY_OFDM(0xD3) /* RF घातer override */



/* Radio रेजिस्टर access decorators. */
#घोषणा B43_LP_RADIO(radio_reg)			(radio_reg)
#घोषणा B43_LP_NORTH(radio_reg)			B43_LP_RADIO(radio_reg)
#घोषणा B43_LP_SOUTH(radio_reg)			B43_LP_RADIO((radio_reg) | 0x4000)


/*** Broadcom 2062 NORTH radio रेजिस्टरs ***/
#घोषणा B2062_N_COMM1				B43_LP_NORTH(0x000) /* Common 01 (north) */
#घोषणा B2062_N_COMM2				B43_LP_NORTH(0x002) /* Common 02 (north) */
#घोषणा B2062_N_COMM3				B43_LP_NORTH(0x003) /* Common 03 (north) */
#घोषणा B2062_N_COMM4				B43_LP_NORTH(0x004) /* Common 04 (north) */
#घोषणा B2062_N_COMM5				B43_LP_NORTH(0x005) /* Common 05 (north) */
#घोषणा B2062_N_COMM6				B43_LP_NORTH(0x006) /* Common 06 (north) */
#घोषणा B2062_N_COMM7				B43_LP_NORTH(0x007) /* Common 07 (north) */
#घोषणा B2062_N_COMM8				B43_LP_NORTH(0x008) /* Common 08 (north) */
#घोषणा B2062_N_COMM9				B43_LP_NORTH(0x009) /* Common 09 (north) */
#घोषणा B2062_N_COMM10				B43_LP_NORTH(0x00A) /* Common 10 (north) */
#घोषणा B2062_N_COMM11				B43_LP_NORTH(0x00B) /* Common 11 (north) */
#घोषणा B2062_N_COMM12				B43_LP_NORTH(0x00C) /* Common 12 (north) */
#घोषणा B2062_N_COMM13				B43_LP_NORTH(0x00D) /* Common 13 (north) */
#घोषणा B2062_N_COMM14				B43_LP_NORTH(0x00E) /* Common 14 (north) */
#घोषणा B2062_N_COMM15				B43_LP_NORTH(0x00F) /* Common 15 (north) */
#घोषणा B2062_N_PDN_CTL0			B43_LP_NORTH(0x010) /* PDN Control 0 (north) */
#घोषणा B2062_N_PDN_CTL1			B43_LP_NORTH(0x011) /* PDN Control 1 (north) */
#घोषणा B2062_N_PDN_CTL2			B43_LP_NORTH(0x012) /* PDN Control 2 (north) */
#घोषणा B2062_N_PDN_CTL3			B43_LP_NORTH(0x013) /* PDN Control 3 (north) */
#घोषणा B2062_N_PDN_CTL4			B43_LP_NORTH(0x014) /* PDN Control 4 (north) */
#घोषणा B2062_N_GEN_CTL0			B43_LP_NORTH(0x015) /* GEN Control 0 (north) */
#घोषणा B2062_N_IQ_CALIB			B43_LP_NORTH(0x016) /* IQ Calibration (north) */
#घोषणा B2062_N_LGENC				B43_LP_NORTH(0x017) /* LGENC (north) */
#घोषणा B2062_N_LGENA_LPF			B43_LP_NORTH(0x018) /* LGENA LPF (north) */
#घोषणा B2062_N_LGENA_BIAS0			B43_LP_NORTH(0x019) /* LGENA Bias 0 (north) */
#घोषणा B2062_N_LGNEA_BIAS1			B43_LP_NORTH(0x01A) /* LGNEA Bias 1 (north) */
#घोषणा B2062_N_LGENA_CTL0			B43_LP_NORTH(0x01B) /* LGENA Control 0 (north) */
#घोषणा B2062_N_LGENA_CTL1			B43_LP_NORTH(0x01C) /* LGENA Control 1 (north) */
#घोषणा B2062_N_LGENA_CTL2			B43_LP_NORTH(0x01D) /* LGENA Control 2 (north) */
#घोषणा B2062_N_LGENA_TUNE0			B43_LP_NORTH(0x01E) /* LGENA Tune 0 (north) */
#घोषणा B2062_N_LGENA_TUNE1			B43_LP_NORTH(0x01F) /* LGENA Tune 1 (north) */
#घोषणा B2062_N_LGENA_TUNE2			B43_LP_NORTH(0x020) /* LGENA Tune 2 (north) */
#घोषणा B2062_N_LGENA_TUNE3			B43_LP_NORTH(0x021) /* LGENA Tune 3 (north) */
#घोषणा B2062_N_LGENA_CTL3			B43_LP_NORTH(0x022) /* LGENA Control 3 (north) */
#घोषणा B2062_N_LGENA_CTL4			B43_LP_NORTH(0x023) /* LGENA Control 4 (north) */
#घोषणा B2062_N_LGENA_CTL5			B43_LP_NORTH(0x024) /* LGENA Control 5 (north) */
#घोषणा B2062_N_LGENA_CTL6			B43_LP_NORTH(0x025) /* LGENA Control 6 (north) */
#घोषणा B2062_N_LGENA_CTL7			B43_LP_NORTH(0x026) /* LGENA Control 7 (north) */
#घोषणा B2062_N_RXA_CTL0			B43_LP_NORTH(0x027) /* RXA Control 0 (north) */
#घोषणा B2062_N_RXA_CTL1			B43_LP_NORTH(0x028) /* RXA Control 1 (north) */
#घोषणा B2062_N_RXA_CTL2			B43_LP_NORTH(0x029) /* RXA Control 2 (north) */
#घोषणा B2062_N_RXA_CTL3			B43_LP_NORTH(0x02A) /* RXA Control 3 (north) */
#घोषणा B2062_N_RXA_CTL4			B43_LP_NORTH(0x02B) /* RXA Control 4 (north) */
#घोषणा B2062_N_RXA_CTL5			B43_LP_NORTH(0x02C) /* RXA Control 5 (north) */
#घोषणा B2062_N_RXA_CTL6			B43_LP_NORTH(0x02D) /* RXA Control 6 (north) */
#घोषणा B2062_N_RXA_CTL7			B43_LP_NORTH(0x02E) /* RXA Control 7 (north) */
#घोषणा B2062_N_RXBB_CTL0			B43_LP_NORTH(0x02F) /* RXBB Control 0 (north) */
#घोषणा B2062_N_RXBB_CTL1			B43_LP_NORTH(0x030) /* RXBB Control 1 (north) */
#घोषणा B2062_N_RXBB_CTL2			B43_LP_NORTH(0x031) /* RXBB Control 2 (north) */
#घोषणा B2062_N_RXBB_GAIN0			B43_LP_NORTH(0x032) /* RXBB Gain 0 (north) */
#घोषणा B2062_N_RXBB_GAIN1			B43_LP_NORTH(0x033) /* RXBB Gain 1 (north) */
#घोषणा B2062_N_RXBB_GAIN2			B43_LP_NORTH(0x034) /* RXBB Gain 2 (north) */
#घोषणा B2062_N_RXBB_GAIN3			B43_LP_NORTH(0x035) /* RXBB Gain 3 (north) */
#घोषणा B2062_N_RXBB_RSSI0			B43_LP_NORTH(0x036) /* RXBB RSSI 0 (north) */
#घोषणा B2062_N_RXBB_RSSI1			B43_LP_NORTH(0x037) /* RXBB RSSI 1 (north) */
#घोषणा B2062_N_RXBB_CALIB0			B43_LP_NORTH(0x038) /* RXBB Calibration0 (north) */
#घोषणा B2062_N_RXBB_CALIB1			B43_LP_NORTH(0x039) /* RXBB Calibration1 (north) */
#घोषणा B2062_N_RXBB_CALIB2			B43_LP_NORTH(0x03A) /* RXBB Calibration2 (north) */
#घोषणा B2062_N_RXBB_BIAS0			B43_LP_NORTH(0x03B) /* RXBB Bias 0 (north) */
#घोषणा B2062_N_RXBB_BIAS1			B43_LP_NORTH(0x03C) /* RXBB Bias 1 (north) */
#घोषणा B2062_N_RXBB_BIAS2			B43_LP_NORTH(0x03D) /* RXBB Bias 2 (north) */
#घोषणा B2062_N_RXBB_BIAS3			B43_LP_NORTH(0x03E) /* RXBB Bias 3 (north) */
#घोषणा B2062_N_RXBB_BIAS4			B43_LP_NORTH(0x03F) /* RXBB Bias 4 (north) */
#घोषणा B2062_N_RXBB_BIAS5			B43_LP_NORTH(0x040) /* RXBB Bias 5 (north) */
#घोषणा B2062_N_RXBB_RSSI2			B43_LP_NORTH(0x041) /* RXBB RSSI 2 (north) */
#घोषणा B2062_N_RXBB_RSSI3			B43_LP_NORTH(0x042) /* RXBB RSSI 3 (north) */
#घोषणा B2062_N_RXBB_RSSI4			B43_LP_NORTH(0x043) /* RXBB RSSI 4 (north) */
#घोषणा B2062_N_RXBB_RSSI5			B43_LP_NORTH(0x044) /* RXBB RSSI 5 (north) */
#घोषणा B2062_N_TX_CTL0				B43_LP_NORTH(0x045) /* TX Control 0 (north) */
#घोषणा B2062_N_TX_CTL1				B43_LP_NORTH(0x046) /* TX Control 1 (north) */
#घोषणा B2062_N_TX_CTL2				B43_LP_NORTH(0x047) /* TX Control 2 (north) */
#घोषणा B2062_N_TX_CTL3				B43_LP_NORTH(0x048) /* TX Control 3 (north) */
#घोषणा B2062_N_TX_CTL4				B43_LP_NORTH(0x049) /* TX Control 4 (north) */
#घोषणा B2062_N_TX_CTL5				B43_LP_NORTH(0x04A) /* TX Control 5 (north) */
#घोषणा B2062_N_TX_CTL6				B43_LP_NORTH(0x04B) /* TX Control 6 (north) */
#घोषणा B2062_N_TX_CTL7				B43_LP_NORTH(0x04C) /* TX Control 7 (north) */
#घोषणा B2062_N_TX_CTL8				B43_LP_NORTH(0x04D) /* TX Control 8 (north) */
#घोषणा B2062_N_TX_CTL9				B43_LP_NORTH(0x04E) /* TX Control 9 (north) */
#घोषणा B2062_N_TX_CTL_A			B43_LP_NORTH(0x04F) /* TX Control A (north) */
#घोषणा B2062_N_TX_GC2G				B43_LP_NORTH(0x050) /* TX GC2G (north) */
#घोषणा B2062_N_TX_GC5G				B43_LP_NORTH(0x051) /* TX GC5G (north) */
#घोषणा B2062_N_TX_TUNE				B43_LP_NORTH(0x052) /* TX Tune (north) */
#घोषणा B2062_N_TX_PAD				B43_LP_NORTH(0x053) /* TX PAD (north) */
#घोषणा B2062_N_TX_PGA				B43_LP_NORTH(0x054) /* TX PGA (north) */
#घोषणा B2062_N_TX_PADAUX			B43_LP_NORTH(0x055) /* TX PADAUX (north) */
#घोषणा B2062_N_TX_PGAAUX			B43_LP_NORTH(0x056) /* TX PGAAUX (north) */
#घोषणा B2062_N_TSSI_CTL0			B43_LP_NORTH(0x057) /* TSSI Control 0 (north) */
#घोषणा B2062_N_TSSI_CTL1			B43_LP_NORTH(0x058) /* TSSI Control 1 (north) */
#घोषणा B2062_N_TSSI_CTL2			B43_LP_NORTH(0x059) /* TSSI Control 2 (north) */
#घोषणा B2062_N_IQ_CALIB_CTL0			B43_LP_NORTH(0x05A) /* IQ Calibration Control 0 (north) */
#घोषणा B2062_N_IQ_CALIB_CTL1			B43_LP_NORTH(0x05B) /* IQ Calibration Control 1 (north) */
#घोषणा B2062_N_IQ_CALIB_CTL2			B43_LP_NORTH(0x05C) /* IQ Calibration Control 2 (north) */
#घोषणा B2062_N_CALIB_TS			B43_LP_NORTH(0x05D) /* Calibration TS (north) */
#घोषणा B2062_N_CALIB_CTL0			B43_LP_NORTH(0x05E) /* Calibration Control 0 (north) */
#घोषणा B2062_N_CALIB_CTL1			B43_LP_NORTH(0x05F) /* Calibration Control 1 (north) */
#घोषणा B2062_N_CALIB_CTL2			B43_LP_NORTH(0x060) /* Calibration Control 2 (north) */
#घोषणा B2062_N_CALIB_CTL3			B43_LP_NORTH(0x061) /* Calibration Control 3 (north) */
#घोषणा B2062_N_CALIB_CTL4			B43_LP_NORTH(0x062) /* Calibration Control 4 (north) */
#घोषणा B2062_N_CALIB_DBG0			B43_LP_NORTH(0x063) /* Calibration Debug 0 (north) */
#घोषणा B2062_N_CALIB_DBG1			B43_LP_NORTH(0x064) /* Calibration Debug 1 (north) */
#घोषणा B2062_N_CALIB_DBG2			B43_LP_NORTH(0x065) /* Calibration Debug 2 (north) */
#घोषणा B2062_N_CALIB_DBG3			B43_LP_NORTH(0x066) /* Calibration Debug 3 (north) */
#घोषणा B2062_N_PSENSE_CTL0			B43_LP_NORTH(0x069) /* PSENSE Control 0 (north) */
#घोषणा B2062_N_PSENSE_CTL1			B43_LP_NORTH(0x06A) /* PSENSE Control 1 (north) */
#घोषणा B2062_N_PSENSE_CTL2			B43_LP_NORTH(0x06B) /* PSENSE Control 2 (north) */
#घोषणा B2062_N_TEST_BUF0			B43_LP_NORTH(0x06C) /* TEST BUF0 (north) */

/*** Broadcom 2062 SOUTH radio रेजिस्टरs ***/
#घोषणा B2062_S_COMM1				B43_LP_SOUTH(0x000) /* Common 01 (south) */
#घोषणा B2062_S_RADIO_ID_CODE			B43_LP_SOUTH(0x001) /* Radio ID code (south) */
#घोषणा B2062_S_COMM2				B43_LP_SOUTH(0x002) /* Common 02 (south) */
#घोषणा B2062_S_COMM3				B43_LP_SOUTH(0x003) /* Common 03 (south) */
#घोषणा B2062_S_COMM4				B43_LP_SOUTH(0x004) /* Common 04 (south) */
#घोषणा B2062_S_COMM5				B43_LP_SOUTH(0x005) /* Common 05 (south) */
#घोषणा B2062_S_COMM6				B43_LP_SOUTH(0x006) /* Common 06 (south) */
#घोषणा B2062_S_COMM7				B43_LP_SOUTH(0x007) /* Common 07 (south) */
#घोषणा B2062_S_COMM8				B43_LP_SOUTH(0x008) /* Common 08 (south) */
#घोषणा B2062_S_COMM9				B43_LP_SOUTH(0x009) /* Common 09 (south) */
#घोषणा B2062_S_COMM10				B43_LP_SOUTH(0x00A) /* Common 10 (south) */
#घोषणा B2062_S_COMM11				B43_LP_SOUTH(0x00B) /* Common 11 (south) */
#घोषणा B2062_S_COMM12				B43_LP_SOUTH(0x00C) /* Common 12 (south) */
#घोषणा B2062_S_COMM13				B43_LP_SOUTH(0x00D) /* Common 13 (south) */
#घोषणा B2062_S_COMM14				B43_LP_SOUTH(0x00E) /* Common 14 (south) */
#घोषणा B2062_S_COMM15				B43_LP_SOUTH(0x00F) /* Common 15 (south) */
#घोषणा B2062_S_PDS_CTL0			B43_LP_SOUTH(0x010) /* PDS Control 0 (south) */
#घोषणा B2062_S_PDS_CTL1			B43_LP_SOUTH(0x011) /* PDS Control 1 (south) */
#घोषणा B2062_S_PDS_CTL2			B43_LP_SOUTH(0x012) /* PDS Control 2 (south) */
#घोषणा B2062_S_PDS_CTL3			B43_LP_SOUTH(0x013) /* PDS Control 3 (south) */
#घोषणा B2062_S_BG_CTL0				B43_LP_SOUTH(0x014) /* BG Control 0 (south) */
#घोषणा B2062_S_BG_CTL1				B43_LP_SOUTH(0x015) /* BG Control 1 (south) */
#घोषणा B2062_S_BG_CTL2				B43_LP_SOUTH(0x016) /* BG Control 2 (south) */
#घोषणा B2062_S_LGENG_CTL0			B43_LP_SOUTH(0x017) /* LGENG Control 00 (south) */
#घोषणा B2062_S_LGENG_CTL1			B43_LP_SOUTH(0x018) /* LGENG Control 01 (south) */
#घोषणा B2062_S_LGENG_CTL2			B43_LP_SOUTH(0x019) /* LGENG Control 02 (south) */
#घोषणा B2062_S_LGENG_CTL3			B43_LP_SOUTH(0x01A) /* LGENG Control 03 (south) */
#घोषणा B2062_S_LGENG_CTL4			B43_LP_SOUTH(0x01B) /* LGENG Control 04 (south) */
#घोषणा B2062_S_LGENG_CTL5			B43_LP_SOUTH(0x01C) /* LGENG Control 05 (south) */
#घोषणा B2062_S_LGENG_CTL6			B43_LP_SOUTH(0x01D) /* LGENG Control 06 (south) */
#घोषणा B2062_S_LGENG_CTL7			B43_LP_SOUTH(0x01E) /* LGENG Control 07 (south) */
#घोषणा B2062_S_LGENG_CTL8			B43_LP_SOUTH(0x01F) /* LGENG Control 08 (south) */
#घोषणा B2062_S_LGENG_CTL9			B43_LP_SOUTH(0x020) /* LGENG Control 09 (south) */
#घोषणा B2062_S_LGENG_CTL10			B43_LP_SOUTH(0x021) /* LGENG Control 10 (south) */
#घोषणा B2062_S_LGENG_CTL11			B43_LP_SOUTH(0x022) /* LGENG Control 11 (south) */
#घोषणा B2062_S_REFPLL_CTL0			B43_LP_SOUTH(0x023) /* REFPLL Control 00 (south) */
#घोषणा B2062_S_REFPLL_CTL1			B43_LP_SOUTH(0x024) /* REFPLL Control 01 (south) */
#घोषणा B2062_S_REFPLL_CTL2			B43_LP_SOUTH(0x025) /* REFPLL Control 02 (south) */
#घोषणा B2062_S_REFPLL_CTL3			B43_LP_SOUTH(0x026) /* REFPLL Control 03 (south) */
#घोषणा B2062_S_REFPLL_CTL4			B43_LP_SOUTH(0x027) /* REFPLL Control 04 (south) */
#घोषणा B2062_S_REFPLL_CTL5			B43_LP_SOUTH(0x028) /* REFPLL Control 05 (south) */
#घोषणा B2062_S_REFPLL_CTL6			B43_LP_SOUTH(0x029) /* REFPLL Control 06 (south) */
#घोषणा B2062_S_REFPLL_CTL7			B43_LP_SOUTH(0x02A) /* REFPLL Control 07 (south) */
#घोषणा B2062_S_REFPLL_CTL8			B43_LP_SOUTH(0x02B) /* REFPLL Control 08 (south) */
#घोषणा B2062_S_REFPLL_CTL9			B43_LP_SOUTH(0x02C) /* REFPLL Control 09 (south) */
#घोषणा B2062_S_REFPLL_CTL10			B43_LP_SOUTH(0x02D) /* REFPLL Control 10 (south) */
#घोषणा B2062_S_REFPLL_CTL11			B43_LP_SOUTH(0x02E) /* REFPLL Control 11 (south) */
#घोषणा B2062_S_REFPLL_CTL12			B43_LP_SOUTH(0x02F) /* REFPLL Control 12 (south) */
#घोषणा B2062_S_REFPLL_CTL13			B43_LP_SOUTH(0x030) /* REFPLL Control 13 (south) */
#घोषणा B2062_S_REFPLL_CTL14			B43_LP_SOUTH(0x031) /* REFPLL Control 14 (south) */
#घोषणा B2062_S_REFPLL_CTL15			B43_LP_SOUTH(0x032) /* REFPLL Control 15 (south) */
#घोषणा B2062_S_REFPLL_CTL16			B43_LP_SOUTH(0x033) /* REFPLL Control 16 (south) */
#घोषणा B2062_S_RFPLL_CTL0			B43_LP_SOUTH(0x034) /* RFPLL Control 00 (south) */
#घोषणा B2062_S_RFPLL_CTL1			B43_LP_SOUTH(0x035) /* RFPLL Control 01 (south) */
#घोषणा B2062_S_RFPLL_CTL2			B43_LP_SOUTH(0x036) /* RFPLL Control 02 (south) */
#घोषणा B2062_S_RFPLL_CTL3			B43_LP_SOUTH(0x037) /* RFPLL Control 03 (south) */
#घोषणा B2062_S_RFPLL_CTL4			B43_LP_SOUTH(0x038) /* RFPLL Control 04 (south) */
#घोषणा B2062_S_RFPLL_CTL5			B43_LP_SOUTH(0x039) /* RFPLL Control 05 (south) */
#घोषणा B2062_S_RFPLL_CTL6			B43_LP_SOUTH(0x03A) /* RFPLL Control 06 (south) */
#घोषणा B2062_S_RFPLL_CTL7			B43_LP_SOUTH(0x03B) /* RFPLL Control 07 (south) */
#घोषणा B2062_S_RFPLL_CTL8			B43_LP_SOUTH(0x03C) /* RFPLL Control 08 (south) */
#घोषणा B2062_S_RFPLL_CTL9			B43_LP_SOUTH(0x03D) /* RFPLL Control 09 (south) */
#घोषणा B2062_S_RFPLL_CTL10			B43_LP_SOUTH(0x03E) /* RFPLL Control 10 (south) */
#घोषणा B2062_S_RFPLL_CTL11			B43_LP_SOUTH(0x03F) /* RFPLL Control 11 (south) */
#घोषणा B2062_S_RFPLL_CTL12			B43_LP_SOUTH(0x040) /* RFPLL Control 12 (south) */
#घोषणा B2062_S_RFPLL_CTL13			B43_LP_SOUTH(0x041) /* RFPLL Control 13 (south) */
#घोषणा B2062_S_RFPLL_CTL14			B43_LP_SOUTH(0x042) /* RFPLL Control 14 (south) */
#घोषणा B2062_S_RFPLL_CTL15			B43_LP_SOUTH(0x043) /* RFPLL Control 15 (south) */
#घोषणा B2062_S_RFPLL_CTL16			B43_LP_SOUTH(0x044) /* RFPLL Control 16 (south) */
#घोषणा B2062_S_RFPLL_CTL17			B43_LP_SOUTH(0x045) /* RFPLL Control 17 (south) */
#घोषणा B2062_S_RFPLL_CTL18			B43_LP_SOUTH(0x046) /* RFPLL Control 18 (south) */
#घोषणा B2062_S_RFPLL_CTL19			B43_LP_SOUTH(0x047) /* RFPLL Control 19 (south) */
#घोषणा B2062_S_RFPLL_CTL20			B43_LP_SOUTH(0x048) /* RFPLL Control 20 (south) */
#घोषणा B2062_S_RFPLL_CTL21			B43_LP_SOUTH(0x049) /* RFPLL Control 21 (south) */
#घोषणा B2062_S_RFPLL_CTL22			B43_LP_SOUTH(0x04A) /* RFPLL Control 22 (south) */
#घोषणा B2062_S_RFPLL_CTL23			B43_LP_SOUTH(0x04B) /* RFPLL Control 23 (south) */
#घोषणा B2062_S_RFPLL_CTL24			B43_LP_SOUTH(0x04C) /* RFPLL Control 24 (south) */
#घोषणा B2062_S_RFPLL_CTL25			B43_LP_SOUTH(0x04D) /* RFPLL Control 25 (south) */
#घोषणा B2062_S_RFPLL_CTL26			B43_LP_SOUTH(0x04E) /* RFPLL Control 26 (south) */
#घोषणा B2062_S_RFPLL_CTL27			B43_LP_SOUTH(0x04F) /* RFPLL Control 27 (south) */
#घोषणा B2062_S_RFPLL_CTL28			B43_LP_SOUTH(0x050) /* RFPLL Control 28 (south) */
#घोषणा B2062_S_RFPLL_CTL29			B43_LP_SOUTH(0x051) /* RFPLL Control 29 (south) */
#घोषणा B2062_S_RFPLL_CTL30			B43_LP_SOUTH(0x052) /* RFPLL Control 30 (south) */
#घोषणा B2062_S_RFPLL_CTL31			B43_LP_SOUTH(0x053) /* RFPLL Control 31 (south) */
#घोषणा B2062_S_RFPLL_CTL32			B43_LP_SOUTH(0x054) /* RFPLL Control 32 (south) */
#घोषणा B2062_S_RFPLL_CTL33			B43_LP_SOUTH(0x055) /* RFPLL Control 33 (south) */
#घोषणा B2062_S_RFPLL_CTL34			B43_LP_SOUTH(0x056) /* RFPLL Control 34 (south) */
#घोषणा B2062_S_RXG_CNT0			B43_LP_SOUTH(0x057) /* RXG Counter 00 (south) */
#घोषणा B2062_S_RXG_CNT1			B43_LP_SOUTH(0x058) /* RXG Counter 01 (south) */
#घोषणा B2062_S_RXG_CNT2			B43_LP_SOUTH(0x059) /* RXG Counter 02 (south) */
#घोषणा B2062_S_RXG_CNT3			B43_LP_SOUTH(0x05A) /* RXG Counter 03 (south) */
#घोषणा B2062_S_RXG_CNT4			B43_LP_SOUTH(0x05B) /* RXG Counter 04 (south) */
#घोषणा B2062_S_RXG_CNT5			B43_LP_SOUTH(0x05C) /* RXG Counter 05 (south) */
#घोषणा B2062_S_RXG_CNT6			B43_LP_SOUTH(0x05D) /* RXG Counter 06 (south) */
#घोषणा B2062_S_RXG_CNT7			B43_LP_SOUTH(0x05E) /* RXG Counter 07 (south) */
#घोषणा B2062_S_RXG_CNT8			B43_LP_SOUTH(0x05F) /* RXG Counter 08 (south) */
#घोषणा B2062_S_RXG_CNT9			B43_LP_SOUTH(0x060) /* RXG Counter 09 (south) */
#घोषणा B2062_S_RXG_CNT10			B43_LP_SOUTH(0x061) /* RXG Counter 10 (south) */
#घोषणा B2062_S_RXG_CNT11			B43_LP_SOUTH(0x062) /* RXG Counter 11 (south) */
#घोषणा B2062_S_RXG_CNT12			B43_LP_SOUTH(0x063) /* RXG Counter 12 (south) */
#घोषणा B2062_S_RXG_CNT13			B43_LP_SOUTH(0x064) /* RXG Counter 13 (south) */
#घोषणा B2062_S_RXG_CNT14			B43_LP_SOUTH(0x065) /* RXG Counter 14 (south) */
#घोषणा B2062_S_RXG_CNT15			B43_LP_SOUTH(0x066) /* RXG Counter 15 (south) */
#घोषणा B2062_S_RXG_CNT16			B43_LP_SOUTH(0x067) /* RXG Counter 16 (south) */
#घोषणा B2062_S_RXG_CNT17			B43_LP_SOUTH(0x068) /* RXG Counter 17 (south) */



/*** Broadcom 2063 radio रेजिस्टरs ***/
#घोषणा B2063_RADIO_ID_CODE			B43_LP_RADIO(0x001) /* Radio ID code */
#घोषणा B2063_COMM1				B43_LP_RADIO(0x000) /* Common 01 */
#घोषणा B2063_COMM2				B43_LP_RADIO(0x002) /* Common 02 */
#घोषणा B2063_COMM3				B43_LP_RADIO(0x003) /* Common 03 */
#घोषणा B2063_COMM4				B43_LP_RADIO(0x004) /* Common 04 */
#घोषणा B2063_COMM5				B43_LP_RADIO(0x005) /* Common 05 */
#घोषणा B2063_COMM6				B43_LP_RADIO(0x006) /* Common 06 */
#घोषणा B2063_COMM7				B43_LP_RADIO(0x007) /* Common 07 */
#घोषणा B2063_COMM8				B43_LP_RADIO(0x008) /* Common 08 */
#घोषणा B2063_COMM9				B43_LP_RADIO(0x009) /* Common 09 */
#घोषणा B2063_COMM10				B43_LP_RADIO(0x00A) /* Common 10 */
#घोषणा B2063_COMM11				B43_LP_RADIO(0x00B) /* Common 11 */
#घोषणा B2063_COMM12				B43_LP_RADIO(0x00C) /* Common 12 */
#घोषणा B2063_COMM13				B43_LP_RADIO(0x00D) /* Common 13 */
#घोषणा B2063_COMM14				B43_LP_RADIO(0x00E) /* Common 14 */
#घोषणा B2063_COMM15				B43_LP_RADIO(0x00F) /* Common 15 */
#घोषणा B2063_COMM16				B43_LP_RADIO(0x010) /* Common 16 */
#घोषणा B2063_COMM17				B43_LP_RADIO(0x011) /* Common 17 */
#घोषणा B2063_COMM18				B43_LP_RADIO(0x012) /* Common 18 */
#घोषणा B2063_COMM19				B43_LP_RADIO(0x013) /* Common 19 */
#घोषणा B2063_COMM20				B43_LP_RADIO(0x014) /* Common 20 */
#घोषणा B2063_COMM21				B43_LP_RADIO(0x015) /* Common 21 */
#घोषणा B2063_COMM22				B43_LP_RADIO(0x016) /* Common 22 */
#घोषणा B2063_COMM23				B43_LP_RADIO(0x017) /* Common 23 */
#घोषणा B2063_COMM24				B43_LP_RADIO(0x018) /* Common 24 */
#घोषणा B2063_PWR_SWITCH_CTL			B43_LP_RADIO(0x019) /* POWER SWITCH Control */
#घोषणा B2063_PLL_SP1				B43_LP_RADIO(0x01A) /* PLL SP 1 */
#घोषणा B2063_PLL_SP2				B43_LP_RADIO(0x01B) /* PLL SP 2 */
#घोषणा B2063_LOGEN_SP1				B43_LP_RADIO(0x01C) /* LOGEN SP 1 */
#घोषणा B2063_LOGEN_SP2				B43_LP_RADIO(0x01D) /* LOGEN SP 2 */
#घोषणा B2063_LOGEN_SP3				B43_LP_RADIO(0x01E) /* LOGEN SP 3 */
#घोषणा B2063_LOGEN_SP4				B43_LP_RADIO(0x01F) /* LOGEN SP 4 */
#घोषणा B2063_LOGEN_SP5				B43_LP_RADIO(0x020) /* LOGEN SP 5 */
#घोषणा B2063_G_RX_SP1				B43_LP_RADIO(0x021) /* G RX SP 1 */
#घोषणा B2063_G_RX_SP2				B43_LP_RADIO(0x022) /* G RX SP 2 */
#घोषणा B2063_G_RX_SP3				B43_LP_RADIO(0x023) /* G RX SP 3 */
#घोषणा B2063_G_RX_SP4				B43_LP_RADIO(0x024) /* G RX SP 4 */
#घोषणा B2063_G_RX_SP5				B43_LP_RADIO(0x025) /* G RX SP 5 */
#घोषणा B2063_G_RX_SP6				B43_LP_RADIO(0x026) /* G RX SP 6 */
#घोषणा B2063_G_RX_SP7				B43_LP_RADIO(0x027) /* G RX SP 7 */
#घोषणा B2063_G_RX_SP8				B43_LP_RADIO(0x028) /* G RX SP 8 */
#घोषणा B2063_G_RX_SP9				B43_LP_RADIO(0x029) /* G RX SP 9 */
#घोषणा B2063_G_RX_SP10				B43_LP_RADIO(0x02A) /* G RX SP 10 */
#घोषणा B2063_G_RX_SP11				B43_LP_RADIO(0x02B) /* G RX SP 11 */
#घोषणा B2063_A_RX_SP1				B43_LP_RADIO(0x02C) /* A RX SP 1 */
#घोषणा B2063_A_RX_SP2				B43_LP_RADIO(0x02D) /* A RX SP 2 */
#घोषणा B2063_A_RX_SP3				B43_LP_RADIO(0x02E) /* A RX SP 3 */
#घोषणा B2063_A_RX_SP4				B43_LP_RADIO(0x02F) /* A RX SP 4 */
#घोषणा B2063_A_RX_SP5				B43_LP_RADIO(0x030) /* A RX SP 5 */
#घोषणा B2063_A_RX_SP6				B43_LP_RADIO(0x031) /* A RX SP 6 */
#घोषणा B2063_A_RX_SP7				B43_LP_RADIO(0x032) /* A RX SP 7 */
#घोषणा B2063_RX_BB_SP1				B43_LP_RADIO(0x033) /* RX BB SP 1 */
#घोषणा B2063_RX_BB_SP2				B43_LP_RADIO(0x034) /* RX BB SP 2 */
#घोषणा B2063_RX_BB_SP3				B43_LP_RADIO(0x035) /* RX BB SP 3 */
#घोषणा B2063_RX_BB_SP4				B43_LP_RADIO(0x036) /* RX BB SP 4 */
#घोषणा B2063_RX_BB_SP5				B43_LP_RADIO(0x037) /* RX BB SP 5 */
#घोषणा B2063_RX_BB_SP6				B43_LP_RADIO(0x038) /* RX BB SP 6 */
#घोषणा B2063_RX_BB_SP7				B43_LP_RADIO(0x039) /* RX BB SP 7 */
#घोषणा B2063_RX_BB_SP8				B43_LP_RADIO(0x03A) /* RX BB SP 8 */
#घोषणा B2063_TX_RF_SP1				B43_LP_RADIO(0x03B) /* TX RF SP 1 */
#घोषणा B2063_TX_RF_SP2				B43_LP_RADIO(0x03C) /* TX RF SP 2 */
#घोषणा B2063_TX_RF_SP3				B43_LP_RADIO(0x03D) /* TX RF SP 3 */
#घोषणा B2063_TX_RF_SP4				B43_LP_RADIO(0x03E) /* TX RF SP 4 */
#घोषणा B2063_TX_RF_SP5				B43_LP_RADIO(0x03F) /* TX RF SP 5 */
#घोषणा B2063_TX_RF_SP6				B43_LP_RADIO(0x040) /* TX RF SP 6 */
#घोषणा B2063_TX_RF_SP7				B43_LP_RADIO(0x041) /* TX RF SP 7 */
#घोषणा B2063_TX_RF_SP8				B43_LP_RADIO(0x042) /* TX RF SP 8 */
#घोषणा B2063_TX_RF_SP9				B43_LP_RADIO(0x043) /* TX RF SP 9 */
#घोषणा B2063_TX_RF_SP10			B43_LP_RADIO(0x044) /* TX RF SP 10 */
#घोषणा B2063_TX_RF_SP11			B43_LP_RADIO(0x045) /* TX RF SP 11 */
#घोषणा B2063_TX_RF_SP12			B43_LP_RADIO(0x046) /* TX RF SP 12 */
#घोषणा B2063_TX_RF_SP13			B43_LP_RADIO(0x047) /* TX RF SP 13 */
#घोषणा B2063_TX_RF_SP14			B43_LP_RADIO(0x048) /* TX RF SP 14 */
#घोषणा B2063_TX_RF_SP15			B43_LP_RADIO(0x049) /* TX RF SP 15 */
#घोषणा B2063_TX_RF_SP16			B43_LP_RADIO(0x04A) /* TX RF SP 16 */
#घोषणा B2063_TX_RF_SP17			B43_LP_RADIO(0x04B) /* TX RF SP 17 */
#घोषणा B2063_PA_SP1				B43_LP_RADIO(0x04C) /* PA SP 1 */
#घोषणा B2063_PA_SP2				B43_LP_RADIO(0x04D) /* PA SP 2 */
#घोषणा B2063_PA_SP3				B43_LP_RADIO(0x04E) /* PA SP 3 */
#घोषणा B2063_PA_SP4				B43_LP_RADIO(0x04F) /* PA SP 4 */
#घोषणा B2063_PA_SP5				B43_LP_RADIO(0x050) /* PA SP 5 */
#घोषणा B2063_PA_SP6				B43_LP_RADIO(0x051) /* PA SP 6 */
#घोषणा B2063_PA_SP7				B43_LP_RADIO(0x052) /* PA SP 7 */
#घोषणा B2063_TX_BB_SP1				B43_LP_RADIO(0x053) /* TX BB SP 1 */
#घोषणा B2063_TX_BB_SP2				B43_LP_RADIO(0x054) /* TX BB SP 2 */
#घोषणा B2063_TX_BB_SP3				B43_LP_RADIO(0x055) /* TX BB SP 3 */
#घोषणा B2063_REG_SP1				B43_LP_RADIO(0x056) /* REG SP 1 */
#घोषणा B2063_BANDGAP_CTL1			B43_LP_RADIO(0x057) /* BANDGAP Control 1 */
#घोषणा B2063_BANDGAP_CTL2			B43_LP_RADIO(0x058) /* BANDGAP Control 2 */
#घोषणा B2063_LPO_CTL1				B43_LP_RADIO(0x059) /* LPO Control 1 */
#घोषणा B2063_RC_CALIB_CTL1			B43_LP_RADIO(0x05A) /* RC Calibration Control 1 */
#घोषणा B2063_RC_CALIB_CTL2			B43_LP_RADIO(0x05B) /* RC Calibration Control 2 */
#घोषणा B2063_RC_CALIB_CTL3			B43_LP_RADIO(0x05C) /* RC Calibration Control 3 */
#घोषणा B2063_RC_CALIB_CTL4			B43_LP_RADIO(0x05D) /* RC Calibration Control 4 */
#घोषणा B2063_RC_CALIB_CTL5			B43_LP_RADIO(0x05E) /* RC Calibration Control 5 */
#घोषणा B2063_RC_CALIB_CTL6			B43_LP_RADIO(0x05F) /* RC Calibration Control 6 */
#घोषणा B2063_RC_CALIB_CTL7			B43_LP_RADIO(0x060) /* RC Calibration Control 7 */
#घोषणा B2063_RC_CALIB_CTL8			B43_LP_RADIO(0x061) /* RC Calibration Control 8 */
#घोषणा B2063_RC_CALIB_CTL9			B43_LP_RADIO(0x062) /* RC Calibration Control 9 */
#घोषणा B2063_RC_CALIB_CTL10			B43_LP_RADIO(0x063) /* RC Calibration Control 10 */
#घोषणा B2063_PLL_JTAG_CALNRST			B43_LP_RADIO(0x064) /* PLL JTAG CALNRST */
#घोषणा B2063_PLL_JTAG_IN_PLL1			B43_LP_RADIO(0x065) /* PLL JTAG IN PLL 1 */
#घोषणा B2063_PLL_JTAG_IN_PLL2			B43_LP_RADIO(0x066) /* PLL JTAG IN PLL 2 */
#घोषणा B2063_PLL_JTAG_PLL_CP1			B43_LP_RADIO(0x067) /* PLL JTAG PLL CP 1 */
#घोषणा B2063_PLL_JTAG_PLL_CP2			B43_LP_RADIO(0x068) /* PLL JTAG PLL CP 2 */
#घोषणा B2063_PLL_JTAG_PLL_CP3			B43_LP_RADIO(0x069) /* PLL JTAG PLL CP 3 */
#घोषणा B2063_PLL_JTAG_PLL_CP4			B43_LP_RADIO(0x06A) /* PLL JTAG PLL CP 4 */
#घोषणा B2063_PLL_JTAG_PLL_CTL1			B43_LP_RADIO(0x06B) /* PLL JTAG PLL Control 1 */
#घोषणा B2063_PLL_JTAG_PLL_LF1			B43_LP_RADIO(0x06C) /* PLL JTAG PLL LF 1 */
#घोषणा B2063_PLL_JTAG_PLL_LF2			B43_LP_RADIO(0x06D) /* PLL JTAG PLL LF 2 */
#घोषणा B2063_PLL_JTAG_PLL_LF3			B43_LP_RADIO(0x06E) /* PLL JTAG PLL LF 3 */
#घोषणा B2063_PLL_JTAG_PLL_LF4			B43_LP_RADIO(0x06F) /* PLL JTAG PLL LF 4 */
#घोषणा B2063_PLL_JTAG_PLL_SG1			B43_LP_RADIO(0x070) /* PLL JTAG PLL SG 1 */
#घोषणा B2063_PLL_JTAG_PLL_SG2			B43_LP_RADIO(0x071) /* PLL JTAG PLL SG 2 */
#घोषणा B2063_PLL_JTAG_PLL_SG3			B43_LP_RADIO(0x072) /* PLL JTAG PLL SG 3 */
#घोषणा B2063_PLL_JTAG_PLL_SG4			B43_LP_RADIO(0x073) /* PLL JTAG PLL SG 4 */
#घोषणा B2063_PLL_JTAG_PLL_SG5			B43_LP_RADIO(0x074) /* PLL JTAG PLL SG 5 */
#घोषणा B2063_PLL_JTAG_PLL_VCO1			B43_LP_RADIO(0x075) /* PLL JTAG PLL VCO 1 */
#घोषणा B2063_PLL_JTAG_PLL_VCO2			B43_LP_RADIO(0x076) /* PLL JTAG PLL VCO 2 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB1		B43_LP_RADIO(0x077) /* PLL JTAG PLL VCO Calibration 1 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB2		B43_LP_RADIO(0x078) /* PLL JTAG PLL VCO Calibration 2 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB3		B43_LP_RADIO(0x079) /* PLL JTAG PLL VCO Calibration 3 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB4		B43_LP_RADIO(0x07A) /* PLL JTAG PLL VCO Calibration 4 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB5		B43_LP_RADIO(0x07B) /* PLL JTAG PLL VCO Calibration 5 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB6		B43_LP_RADIO(0x07C) /* PLL JTAG PLL VCO Calibration 6 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB7		B43_LP_RADIO(0x07D) /* PLL JTAG PLL VCO Calibration 7 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB8		B43_LP_RADIO(0x07E) /* PLL JTAG PLL VCO Calibration 8 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB9		B43_LP_RADIO(0x07F) /* PLL JTAG PLL VCO Calibration 9 */
#घोषणा B2063_PLL_JTAG_PLL_VCO_CALIB10		B43_LP_RADIO(0x080) /* PLL JTAG PLL VCO Calibration 10 */
#घोषणा B2063_PLL_JTAG_PLL_XTAL_12		B43_LP_RADIO(0x081) /* PLL JTAG PLL XTAL 1 2 */
#घोषणा B2063_PLL_JTAG_PLL_XTAL3		B43_LP_RADIO(0x082) /* PLL JTAG PLL XTAL 3 */
#घोषणा B2063_LOGEN_ACL1			B43_LP_RADIO(0x083) /* LOGEN ACL 1 */
#घोषणा B2063_LOGEN_ACL2			B43_LP_RADIO(0x084) /* LOGEN ACL 2 */
#घोषणा B2063_LOGEN_ACL3			B43_LP_RADIO(0x085) /* LOGEN ACL 3 */
#घोषणा B2063_LOGEN_ACL4			B43_LP_RADIO(0x086) /* LOGEN ACL 4 */
#घोषणा B2063_LOGEN_ACL5			B43_LP_RADIO(0x087) /* LOGEN ACL 5 */
#घोषणा B2063_LO_CALIB_INPUTS			B43_LP_RADIO(0x088) /* LO Calibration INPUTS */
#घोषणा B2063_LO_CALIB_CTL1			B43_LP_RADIO(0x089) /* LO Calibration Control 1 */
#घोषणा B2063_LO_CALIB_CTL2			B43_LP_RADIO(0x08A) /* LO Calibration Control 2 */
#घोषणा B2063_LO_CALIB_CTL3			B43_LP_RADIO(0x08B) /* LO Calibration Control 3 */
#घोषणा B2063_LO_CALIB_WAITCNT			B43_LP_RADIO(0x08C) /* LO Calibration WAITCNT */
#घोषणा B2063_LO_CALIB_OVR1			B43_LP_RADIO(0x08D) /* LO Calibration OVR 1 */
#घोषणा B2063_LO_CALIB_OVR2			B43_LP_RADIO(0x08E) /* LO Calibration OVR 2 */
#घोषणा B2063_LO_CALIB_OVAL1			B43_LP_RADIO(0x08F) /* LO Calibration OVAL 1 */
#घोषणा B2063_LO_CALIB_OVAL2			B43_LP_RADIO(0x090) /* LO Calibration OVAL 2 */
#घोषणा B2063_LO_CALIB_OVAL3			B43_LP_RADIO(0x091) /* LO Calibration OVAL 3 */
#घोषणा B2063_LO_CALIB_OVAL4			B43_LP_RADIO(0x092) /* LO Calibration OVAL 4 */
#घोषणा B2063_LO_CALIB_OVAL5			B43_LP_RADIO(0x093) /* LO Calibration OVAL 5 */
#घोषणा B2063_LO_CALIB_OVAL6			B43_LP_RADIO(0x094) /* LO Calibration OVAL 6 */
#घोषणा B2063_LO_CALIB_OVAL7			B43_LP_RADIO(0x095) /* LO Calibration OVAL 7 */
#घोषणा B2063_LO_CALIB_CALVLD1			B43_LP_RADIO(0x096) /* LO Calibration CALVLD 1 */
#घोषणा B2063_LO_CALIB_CALVLD2			B43_LP_RADIO(0x097) /* LO Calibration CALVLD 2 */
#घोषणा B2063_LO_CALIB_CVAL1			B43_LP_RADIO(0x098) /* LO Calibration CVAL 1 */
#घोषणा B2063_LO_CALIB_CVAL2			B43_LP_RADIO(0x099) /* LO Calibration CVAL 2 */
#घोषणा B2063_LO_CALIB_CVAL3			B43_LP_RADIO(0x09A) /* LO Calibration CVAL 3 */
#घोषणा B2063_LO_CALIB_CVAL4			B43_LP_RADIO(0x09B) /* LO Calibration CVAL 4 */
#घोषणा B2063_LO_CALIB_CVAL5			B43_LP_RADIO(0x09C) /* LO Calibration CVAL 5 */
#घोषणा B2063_LO_CALIB_CVAL6			B43_LP_RADIO(0x09D) /* LO Calibration CVAL 6 */
#घोषणा B2063_LO_CALIB_CVAL7			B43_LP_RADIO(0x09E) /* LO Calibration CVAL 7 */
#घोषणा B2063_LOGEN_CALIB_EN			B43_LP_RADIO(0x09F) /* LOGEN Calibration EN */
#घोषणा B2063_LOGEN_PEAKDET1			B43_LP_RADIO(0x0A0) /* LOGEN PEAKDET 1 */
#घोषणा B2063_LOGEN_RCCR1			B43_LP_RADIO(0x0A1) /* LOGEN RCCR 1 */
#घोषणा B2063_LOGEN_VCOBUF1			B43_LP_RADIO(0x0A2) /* LOGEN VCOBUF 1 */
#घोषणा B2063_LOGEN_MIXER1			B43_LP_RADIO(0x0A3) /* LOGEN MIXER 1 */
#घोषणा B2063_LOGEN_MIXER2			B43_LP_RADIO(0x0A4) /* LOGEN MIXER 2 */
#घोषणा B2063_LOGEN_BUF1			B43_LP_RADIO(0x0A5) /* LOGEN BUF 1 */
#घोषणा B2063_LOGEN_BUF2			B43_LP_RADIO(0x0A6) /* LOGEN BUF 2 */
#घोषणा B2063_LOGEN_DIV1			B43_LP_RADIO(0x0A7) /* LOGEN DIV 1 */
#घोषणा B2063_LOGEN_DIV2			B43_LP_RADIO(0x0A8) /* LOGEN DIV 2 */
#घोषणा B2063_LOGEN_DIV3			B43_LP_RADIO(0x0A9) /* LOGEN DIV 3 */
#घोषणा B2063_LOGEN_CBUFRX1			B43_LP_RADIO(0x0AA) /* LOGEN CBUFRX 1 */
#घोषणा B2063_LOGEN_CBUFRX2			B43_LP_RADIO(0x0AB) /* LOGEN CBUFRX 2 */
#घोषणा B2063_LOGEN_CBUFTX1			B43_LP_RADIO(0x0AC) /* LOGEN CBUFTX 1 */
#घोषणा B2063_LOGEN_CBUFTX2			B43_LP_RADIO(0x0AD) /* LOGEN CBUFTX 2 */
#घोषणा B2063_LOGEN_IDAC1			B43_LP_RADIO(0x0AE) /* LOGEN IDAC 1 */
#घोषणा B2063_LOGEN_SPARE1			B43_LP_RADIO(0x0AF) /* LOGEN SPARE 1 */
#घोषणा B2063_LOGEN_SPARE2			B43_LP_RADIO(0x0B0) /* LOGEN SPARE 2 */
#घोषणा B2063_LOGEN_SPARE3			B43_LP_RADIO(0x0B1) /* LOGEN SPARE 3 */
#घोषणा B2063_G_RX_1ST1				B43_LP_RADIO(0x0B2) /* G RX 1ST 1 */
#घोषणा B2063_G_RX_1ST2				B43_LP_RADIO(0x0B3) /* G RX 1ST 2 */
#घोषणा B2063_G_RX_1ST3				B43_LP_RADIO(0x0B4) /* G RX 1ST 3 */
#घोषणा B2063_G_RX_2ND1				B43_LP_RADIO(0x0B5) /* G RX 2ND 1 */
#घोषणा B2063_G_RX_2ND2				B43_LP_RADIO(0x0B6) /* G RX 2ND 2 */
#घोषणा B2063_G_RX_2ND3				B43_LP_RADIO(0x0B7) /* G RX 2ND 3 */
#घोषणा B2063_G_RX_2ND4				B43_LP_RADIO(0x0B8) /* G RX 2ND 4 */
#घोषणा B2063_G_RX_2ND5				B43_LP_RADIO(0x0B9) /* G RX 2ND 5 */
#घोषणा B2063_G_RX_2ND6				B43_LP_RADIO(0x0BA) /* G RX 2ND 6 */
#घोषणा B2063_G_RX_2ND7				B43_LP_RADIO(0x0BB) /* G RX 2ND 7 */
#घोषणा B2063_G_RX_2ND8				B43_LP_RADIO(0x0BC) /* G RX 2ND 8 */
#घोषणा B2063_G_RX_PS1				B43_LP_RADIO(0x0BD) /* G RX PS 1 */
#घोषणा B2063_G_RX_PS2				B43_LP_RADIO(0x0BE) /* G RX PS 2 */
#घोषणा B2063_G_RX_PS3				B43_LP_RADIO(0x0BF) /* G RX PS 3 */
#घोषणा B2063_G_RX_PS4				B43_LP_RADIO(0x0C0) /* G RX PS 4 */
#घोषणा B2063_G_RX_PS5				B43_LP_RADIO(0x0C1) /* G RX PS 5 */
#घोषणा B2063_G_RX_MIX1				B43_LP_RADIO(0x0C2) /* G RX MIX 1 */
#घोषणा B2063_G_RX_MIX2				B43_LP_RADIO(0x0C3) /* G RX MIX 2 */
#घोषणा B2063_G_RX_MIX3				B43_LP_RADIO(0x0C4) /* G RX MIX 3 */
#घोषणा B2063_G_RX_MIX4				B43_LP_RADIO(0x0C5) /* G RX MIX 4 */
#घोषणा B2063_G_RX_MIX5				B43_LP_RADIO(0x0C6) /* G RX MIX 5 */
#घोषणा B2063_G_RX_MIX6				B43_LP_RADIO(0x0C7) /* G RX MIX 6 */
#घोषणा B2063_G_RX_MIX7				B43_LP_RADIO(0x0C8) /* G RX MIX 7 */
#घोषणा B2063_G_RX_MIX8				B43_LP_RADIO(0x0C9) /* G RX MIX 8 */
#घोषणा B2063_G_RX_PDET1			B43_LP_RADIO(0x0CA) /* G RX PDET 1 */
#घोषणा B2063_G_RX_SPARES1			B43_LP_RADIO(0x0CB) /* G RX SPARES 1 */
#घोषणा B2063_G_RX_SPARES2			B43_LP_RADIO(0x0CC) /* G RX SPARES 2 */
#घोषणा B2063_G_RX_SPARES3			B43_LP_RADIO(0x0CD) /* G RX SPARES 3 */
#घोषणा B2063_A_RX_1ST1				B43_LP_RADIO(0x0CE) /* A RX 1ST 1 */
#घोषणा B2063_A_RX_1ST2				B43_LP_RADIO(0x0CF) /* A RX 1ST 2 */
#घोषणा B2063_A_RX_1ST3				B43_LP_RADIO(0x0D0) /* A RX 1ST 3 */
#घोषणा B2063_A_RX_1ST4				B43_LP_RADIO(0x0D1) /* A RX 1ST 4 */
#घोषणा B2063_A_RX_1ST5				B43_LP_RADIO(0x0D2) /* A RX 1ST 5 */
#घोषणा B2063_A_RX_2ND1				B43_LP_RADIO(0x0D3) /* A RX 2ND 1 */
#घोषणा B2063_A_RX_2ND2				B43_LP_RADIO(0x0D4) /* A RX 2ND 2 */
#घोषणा B2063_A_RX_2ND3				B43_LP_RADIO(0x0D5) /* A RX 2ND 3 */
#घोषणा B2063_A_RX_2ND4				B43_LP_RADIO(0x0D6) /* A RX 2ND 4 */
#घोषणा B2063_A_RX_2ND5				B43_LP_RADIO(0x0D7) /* A RX 2ND 5 */
#घोषणा B2063_A_RX_2ND6				B43_LP_RADIO(0x0D8) /* A RX 2ND 6 */
#घोषणा B2063_A_RX_2ND7				B43_LP_RADIO(0x0D9) /* A RX 2ND 7 */
#घोषणा B2063_A_RX_PS1				B43_LP_RADIO(0x0DA) /* A RX PS 1 */
#घोषणा B2063_A_RX_PS2				B43_LP_RADIO(0x0DB) /* A RX PS 2 */
#घोषणा B2063_A_RX_PS3				B43_LP_RADIO(0x0DC) /* A RX PS 3 */
#घोषणा B2063_A_RX_PS4				B43_LP_RADIO(0x0DD) /* A RX PS 4 */
#घोषणा B2063_A_RX_PS5				B43_LP_RADIO(0x0DE) /* A RX PS 5 */
#घोषणा B2063_A_RX_PS6				B43_LP_RADIO(0x0DF) /* A RX PS 6 */
#घोषणा B2063_A_RX_MIX1				B43_LP_RADIO(0x0E0) /* A RX MIX 1 */
#घोषणा B2063_A_RX_MIX2				B43_LP_RADIO(0x0E1) /* A RX MIX 2 */
#घोषणा B2063_A_RX_MIX3				B43_LP_RADIO(0x0E2) /* A RX MIX 3 */
#घोषणा B2063_A_RX_MIX4				B43_LP_RADIO(0x0E3) /* A RX MIX 4 */
#घोषणा B2063_A_RX_MIX5				B43_LP_RADIO(0x0E4) /* A RX MIX 5 */
#घोषणा B2063_A_RX_MIX6				B43_LP_RADIO(0x0E5) /* A RX MIX 6 */
#घोषणा B2063_A_RX_MIX7				B43_LP_RADIO(0x0E6) /* A RX MIX 7 */
#घोषणा B2063_A_RX_MIX8				B43_LP_RADIO(0x0E7) /* A RX MIX 8 */
#घोषणा B2063_A_RX_PWRDET1			B43_LP_RADIO(0x0E8) /* A RX PWRDET 1 */
#घोषणा B2063_A_RX_SPARE1			B43_LP_RADIO(0x0E9) /* A RX SPARE 1 */
#घोषणा B2063_A_RX_SPARE2			B43_LP_RADIO(0x0EA) /* A RX SPARE 2 */
#घोषणा B2063_A_RX_SPARE3			B43_LP_RADIO(0x0EB) /* A RX SPARE 3 */
#घोषणा B2063_RX_TIA_CTL1			B43_LP_RADIO(0x0EC) /* RX TIA Control 1 */
#घोषणा B2063_RX_TIA_CTL2			B43_LP_RADIO(0x0ED) /* RX TIA Control 2 */
#घोषणा B2063_RX_TIA_CTL3			B43_LP_RADIO(0x0EE) /* RX TIA Control 3 */
#घोषणा B2063_RX_TIA_CTL4			B43_LP_RADIO(0x0EF) /* RX TIA Control 4 */
#घोषणा B2063_RX_TIA_CTL5			B43_LP_RADIO(0x0F0) /* RX TIA Control 5 */
#घोषणा B2063_RX_TIA_CTL6			B43_LP_RADIO(0x0F1) /* RX TIA Control 6 */
#घोषणा B2063_RX_BB_CTL1			B43_LP_RADIO(0x0F2) /* RX BB Control 1 */
#घोषणा B2063_RX_BB_CTL2			B43_LP_RADIO(0x0F3) /* RX BB Control 2 */
#घोषणा B2063_RX_BB_CTL3			B43_LP_RADIO(0x0F4) /* RX BB Control 3 */
#घोषणा B2063_RX_BB_CTL4			B43_LP_RADIO(0x0F5) /* RX BB Control 4 */
#घोषणा B2063_RX_BB_CTL5			B43_LP_RADIO(0x0F6) /* RX BB Control 5 */
#घोषणा B2063_RX_BB_CTL6			B43_LP_RADIO(0x0F7) /* RX BB Control 6 */
#घोषणा B2063_RX_BB_CTL7			B43_LP_RADIO(0x0F8) /* RX BB Control 7 */
#घोषणा B2063_RX_BB_CTL8			B43_LP_RADIO(0x0F9) /* RX BB Control 8 */
#घोषणा B2063_RX_BB_CTL9			B43_LP_RADIO(0x0FA) /* RX BB Control 9 */
#घोषणा B2063_TX_RF_CTL1			B43_LP_RADIO(0x0FB) /* TX RF Control 1 */
#घोषणा B2063_TX_RF_IDAC_LO_RF_I		B43_LP_RADIO(0x0FC) /* TX RF IDAC LO RF I */
#घोषणा B2063_TX_RF_IDAC_LO_RF_Q		B43_LP_RADIO(0x0FD) /* TX RF IDAC LO RF Q */
#घोषणा B2063_TX_RF_IDAC_LO_BB_I		B43_LP_RADIO(0x0FE) /* TX RF IDAC LO BB I */
#घोषणा B2063_TX_RF_IDAC_LO_BB_Q		B43_LP_RADIO(0x0FF) /* TX RF IDAC LO BB Q */
#घोषणा B2063_TX_RF_CTL2			B43_LP_RADIO(0x100) /* TX RF Control 2 */
#घोषणा B2063_TX_RF_CTL3			B43_LP_RADIO(0x101) /* TX RF Control 3 */
#घोषणा B2063_TX_RF_CTL4			B43_LP_RADIO(0x102) /* TX RF Control 4 */
#घोषणा B2063_TX_RF_CTL5			B43_LP_RADIO(0x103) /* TX RF Control 5 */
#घोषणा B2063_TX_RF_CTL6			B43_LP_RADIO(0x104) /* TX RF Control 6 */
#घोषणा B2063_TX_RF_CTL7			B43_LP_RADIO(0x105) /* TX RF Control 7 */
#घोषणा B2063_TX_RF_CTL8			B43_LP_RADIO(0x106) /* TX RF Control 8 */
#घोषणा B2063_TX_RF_CTL9			B43_LP_RADIO(0x107) /* TX RF Control 9 */
#घोषणा B2063_TX_RF_CTL10			B43_LP_RADIO(0x108) /* TX RF Control 10 */
#घोषणा B2063_TX_RF_CTL14			B43_LP_RADIO(0x109) /* TX RF Control 14 */
#घोषणा B2063_TX_RF_CTL15			B43_LP_RADIO(0x10A) /* TX RF Control 15 */
#घोषणा B2063_PA_CTL1				B43_LP_RADIO(0x10B) /* PA Control 1 */
#घोषणा B2063_PA_CTL2				B43_LP_RADIO(0x10C) /* PA Control 2 */
#घोषणा B2063_PA_CTL3				B43_LP_RADIO(0x10D) /* PA Control 3 */
#घोषणा B2063_PA_CTL4				B43_LP_RADIO(0x10E) /* PA Control 4 */
#घोषणा B2063_PA_CTL5				B43_LP_RADIO(0x10F) /* PA Control 5 */
#घोषणा B2063_PA_CTL6				B43_LP_RADIO(0x110) /* PA Control 6 */
#घोषणा B2063_PA_CTL7				B43_LP_RADIO(0x111) /* PA Control 7 */
#घोषणा B2063_PA_CTL8				B43_LP_RADIO(0x112) /* PA Control 8 */
#घोषणा B2063_PA_CTL9				B43_LP_RADIO(0x113) /* PA Control 9 */
#घोषणा B2063_PA_CTL10				B43_LP_RADIO(0x114) /* PA Control 10 */
#घोषणा B2063_PA_CTL11				B43_LP_RADIO(0x115) /* PA Control 11 */
#घोषणा B2063_PA_CTL12				B43_LP_RADIO(0x116) /* PA Control 12 */
#घोषणा B2063_PA_CTL13				B43_LP_RADIO(0x117) /* PA Control 13 */
#घोषणा B2063_TX_BB_CTL1			B43_LP_RADIO(0x118) /* TX BB Control 1 */
#घोषणा B2063_TX_BB_CTL2			B43_LP_RADIO(0x119) /* TX BB Control 2 */
#घोषणा B2063_TX_BB_CTL3			B43_LP_RADIO(0x11A) /* TX BB Control 3 */
#घोषणा B2063_TX_BB_CTL4			B43_LP_RADIO(0x11B) /* TX BB Control 4 */
#घोषणा B2063_GPIO_CTL1				B43_LP_RADIO(0x11C) /* GPIO Control 1 */
#घोषणा B2063_VREG_CTL1				B43_LP_RADIO(0x11D) /* VREG Control 1 */
#घोषणा B2063_AMUX_CTL1				B43_LP_RADIO(0x11E) /* AMUX Control 1 */
#घोषणा B2063_IQ_CALIB_GVAR			B43_LP_RADIO(0x11F) /* IQ Calibration GVAR */
#घोषणा B2063_IQ_CALIB_CTL1			B43_LP_RADIO(0x120) /* IQ Calibration Control 1 */
#घोषणा B2063_IQ_CALIB_CTL2			B43_LP_RADIO(0x121) /* IQ Calibration Control 2 */
#घोषणा B2063_TEMPSENSE_CTL1			B43_LP_RADIO(0x122) /* TEMPSENSE Control 1 */
#घोषणा B2063_TEMPSENSE_CTL2			B43_LP_RADIO(0x123) /* TEMPSENSE Control 2 */
#घोषणा B2063_TX_RX_LOOPBACK1			B43_LP_RADIO(0x124) /* TX/RX LOOPBACK 1 */
#घोषणा B2063_TX_RX_LOOPBACK2			B43_LP_RADIO(0x125) /* TX/RX LOOPBACK 2 */
#घोषणा B2063_EXT_TSSI_CTL1			B43_LP_RADIO(0x126) /* EXT TSSI Control 1 */
#घोषणा B2063_EXT_TSSI_CTL2			B43_LP_RADIO(0x127) /* EXT TSSI Control 2 */
#घोषणा B2063_AFE_CTL				B43_LP_RADIO(0x128) /* AFE Control */



क्रमागत b43_lpphy_txpctl_mode अणु
	B43_LPPHY_TXPCTL_UNKNOWN = 0,
	B43_LPPHY_TXPCTL_OFF,	/* TX घातer control is OFF */
	B43_LPPHY_TXPCTL_SW,	/* TX घातer control is set to Software */
	B43_LPPHY_TXPCTL_HW,	/* TX घातer control is set to Hardware */
पूर्ण;

काष्ठा b43_phy_lp अणु
	/* Current TX घातer control mode. */
	क्रमागत b43_lpphy_txpctl_mode txpctl_mode;

	/* Transmit isolation medium band */
	u8 tx_isolation_med_band;
	/* Transmit isolation low band */
	u8 tx_isolation_low_band;
	/* Transmit isolation high band */
	u8 tx_isolation_hi_band;

	/* Max transmit घातer medium band */
	u16 max_tx_pwr_med_band;
	/* Max transmit घातer low band */
	u16 max_tx_pwr_low_band;
	/* Max transmit घातer high band */
	u16 max_tx_pwr_hi_band;

	/* FIXME What are these used क्रम? */
	/* FIXME Is 15 the correct array size? */
	u16 tx_max_rate[15];
	u16 tx_max_ratel[15];
	u16 tx_max_rateh[15];

	/* Transmit घातer arrays */
	s16 txpa[3], txpal[3], txpah[3];

	/* Receive घातer offset */
	u8 rx_pwr_offset;

	/* TSSI transmit count */
	u16 tssi_tx_count;
	/* TSSI index */
	u16 tssi_idx; /* FIXME initial value? */
	/* TSSI npt */
	u16 tssi_npt; /* FIXME initial value? */

	/* Target TX frequency */
	u16 tgt_tx_freq; /* FIXME initial value? */

	/* Transmit घातer index override */
	s8 tx_pwr_idx_over; /* FIXME initial value? */

	/* RSSI vf */
	u8 rssi_vf;
	/* RSSI vc */
	u8 rssi_vc;
	/* RSSI gs */
	u8 rssi_gs;

	/* RC cap */
	u8 rc_cap;
	/* BX arch */
	u8 bx_arch;

	/* Full calibration channel */
	u8 full_calib_chan;

	/* Transmit iqlocal best coeffs */
	bool tx_iqloc_best_coeffs_valid;
	u8 tx_iqloc_best_coeffs[11];

	/* Used क्रम "Save/Restore Dig Filt State" */
	u16 dig_flt_state[9];

	bool crs_usr_disable, crs_sys_disable;

	अचिन्हित पूर्णांक pभाग;

	/* The channel we are tuned to */
	u8 channel;

	/* The active antenna भागersity mode */
	पूर्णांक antenna;

	/* Frequency of the active TX tone */
	पूर्णांक tx_tone_freq;
पूर्ण;

क्रमागत tssi_mux_mode अणु
	TSSI_MUX_PREPA,
	TSSI_MUX_POSTPA,
	TSSI_MUX_EXT,
पूर्ण;

काष्ठा b43_phy_operations;
बाह्य स्थिर काष्ठा b43_phy_operations b43_phyops_lp;

#पूर्ण_अगर /* LINUX_B43_PHY_LP_H_ */
