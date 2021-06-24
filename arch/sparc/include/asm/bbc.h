<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * bbc.h: Defines क्रम BootBus Controller found on UltraSPARC-III
 *        प्रणालीs.
 *
 * Copyright (C) 2000 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _SPARC64_BBC_H
#घोषणा _SPARC64_BBC_H

/* Register sizes are indicated by "B" (Byte, 1-byte),
 * "H" (Half-word, 2 bytes), "W" (Word, 4 bytes) or
 * "Q" (Quad, 8 bytes) inside brackets.
 */

#घोषणा BBC_AID		0x00	/* [B] Agent ID			*/
#घोषणा BBC_DEVP	0x01	/* [B] Device Present		*/
#घोषणा BBC_ARB		0x02	/* [B] Arbitration		*/
#घोषणा BBC_QUIESCE	0x03	/* [B] Quiesce			*/
#घोषणा BBC_WDACTION	0x04	/* [B] Watchकरोg Action		*/
#घोषणा BBC_SPG		0x06	/* [B] Soft POR Gen		*/
#घोषणा BBC_SXG		0x07	/* [B] Soft XIR Gen		*/
#घोषणा BBC_PSRC	0x08	/* [W] POR Source		*/
#घोषणा BBC_XSRC	0x0c	/* [B] XIR Source		*/
#घोषणा BBC_CSC		0x0d	/* [B] Clock Synthesizers Control*/
#घोषणा BBC_ES_CTRL	0x0e	/* [H] Energy Star Control	*/
#घोषणा BBC_ES_ACT	0x10	/* [W] E* Assert Change Time	*/
#घोषणा BBC_ES_DACT	0x14	/* [B] E* De-Assert Change Time	*/
#घोषणा BBC_ES_DABT	0x15	/* [B] E* De-Assert Bypass Time	*/
#घोषणा BBC_ES_ABT	0x16	/* [H] E* Assert Bypass Time	*/
#घोषणा BBC_ES_PST	0x18	/* [W] E* PLL Settle Time	*/
#घोषणा BBC_ES_FSL	0x1c	/* [W] E* Frequency Switch Latency*/
#घोषणा BBC_EBUST	0x20	/* [Q] EBUS Timing		*/
#घोषणा BBC_JTAG_CMD	0x28	/* [W] JTAG+ Command		*/
#घोषणा BBC_JTAG_CTRL	0x2c	/* [B] JTAG+ Control		*/
#घोषणा BBC_I2C_SEL	0x2d	/* [B] I2C Selection		*/
#घोषणा BBC_I2C_0_S1	0x2e	/* [B] I2C ctrlr-0 reg S1	*/
#घोषणा BBC_I2C_0_S0	0x2f	/* [B] I2C ctrlr-0 regs S0,S0',S2,S3*/
#घोषणा BBC_I2C_1_S1	0x30	/* [B] I2C ctrlr-1 reg S1	*/
#घोषणा BBC_I2C_1_S0	0x31	/* [B] I2C ctrlr-1 regs S0,S0',S2,S3*/
#घोषणा BBC_KBD_BEEP	0x32	/* [B] Keyboard Beep		*/
#घोषणा BBC_KBD_BCNT	0x34	/* [W] Keyboard Beep Counter	*/

#घोषणा BBC_REGS_SIZE	0x40

/* There is a 2K scratch ram area at offset 0x80000 but I करोubt
 * we will use it क्रम anything.
 */

/* Agent ID रेजिस्टर.  This रेजिस्टर shows the Safari Agent ID
 * क्रम the processors.  The value वापसed depends upon which
 * cpu is पढ़ोing the रेजिस्टर.
 */
#घोषणा BBC_AID_ID	0x07	/* Safari ID		*/
#घोषणा BBC_AID_RESV	0xf8	/* Reserved		*/

/* Device Present रेजिस्टर.  One can determine which cpus are actually
 * present in the machine by पूर्णांकerrogating this रेजिस्टर.
 */
#घोषणा BBC_DEVP_CPU0	0x01	/* Processor 0 present	*/
#घोषणा BBC_DEVP_CPU1	0x02	/* Processor 1 present	*/
#घोषणा BBC_DEVP_CPU2	0x04	/* Processor 2 present	*/
#घोषणा BBC_DEVP_CPU3	0x08	/* Processor 3 present	*/
#घोषणा BBC_DEVP_RESV	0xf0	/* Reserved		*/

/* Arbitration रेजिस्टर.  This रेजिस्टर is used to block access to
 * the BBC from a particular cpu.
 */
#घोषणा BBC_ARB_CPU0	0x01	/* Enable cpu 0 BBC arbitratrion */
#घोषणा BBC_ARB_CPU1	0x02	/* Enable cpu 1 BBC arbitratrion */
#घोषणा BBC_ARB_CPU2	0x04	/* Enable cpu 2 BBC arbitratrion */
#घोषणा BBC_ARB_CPU3	0x08	/* Enable cpu 3 BBC arbitratrion */
#घोषणा BBC_ARB_RESV	0xf0	/* Reserved			 */

/* Quiesce रेजिस्टर.  Bus and BBC segments क्रम cpus can be disabled
 * with this रेजिस्टर, ie. क्रम hot plugging.
 */
#घोषणा BBC_QUIESCE_S02	0x01	/* Quiesce Safari segment क्रम cpu 0 and 2 */
#घोषणा BBC_QUIESCE_S13	0x02	/* Quiesce Safari segment क्रम cpu 1 and 3 */
#घोषणा BBC_QUIESCE_B02	0x04	/* Quiesce BBC segment क्रम cpu 0 and 2    */
#घोषणा BBC_QUIESCE_B13	0x08	/* Quiesce BBC segment क्रम cpu 1 and 3    */
#घोषणा BBC_QUIESCE_FD0 0x10	/* Disable Fatal_Error[0] reporting	  */
#घोषणा BBC_QUIESCE_FD1 0x20	/* Disable Fatal_Error[1] reporting	  */
#घोषणा BBC_QUIESCE_FD2 0x40	/* Disable Fatal_Error[2] reporting	  */
#घोषणा BBC_QUIESCE_FD3 0x80	/* Disable Fatal_Error[3] reporting	  */

/* Watchकरोg Action रेजिस्टर.  When the watchकरोg device समयr expires
 * a line is enabled to the BBC.  The action BBC takes when this line
 * is निश्चितed can be controlled by this regiser.
 */
#घोषणा BBC_WDACTION_RST  0x01	/* When set, watchकरोg causes प्रणाली reset.
				 * When clear, BBC ignores watchकरोg संकेत.
				 */
#घोषणा BBC_WDACTION_RESV 0xfe	/* Reserved */

/* Soft_POR_GEN रेजिस्टर.  The POR (Power On Reset) संकेत may be निश्चितed
 * क्रम specअगरic processors or all processors via this रेजिस्टर.
 */
#घोषणा BBC_SPG_CPU0	0x01 /* Assert POR क्रम processor 0	*/
#घोषणा BBC_SPG_CPU1	0x02 /* Assert POR क्रम processor 1	*/
#घोषणा BBC_SPG_CPU2	0x04 /* Assert POR क्रम processor 2	*/
#घोषणा BBC_SPG_CPU3	0x08 /* Assert POR क्रम processor 3	*/
#घोषणा BBC_SPG_CPUALL	0x10 /* Reset all processors and reset
			      * the entire प्रणाली.
			      */
#घोषणा BBC_SPG_RESV	0xe0 /* Reserved			*/

/* Soft_XIR_GEN रेजिस्टर.  The XIR (eXternally Initiated Reset) संकेत
 * may be निश्चितed to specअगरic processors via this रेजिस्टर.
 */
#घोषणा BBC_SXG_CPU0	0x01 /* Assert XIR क्रम processor 0	*/
#घोषणा BBC_SXG_CPU1	0x02 /* Assert XIR क्रम processor 1	*/
#घोषणा BBC_SXG_CPU2	0x04 /* Assert XIR क्रम processor 2	*/
#घोषणा BBC_SXG_CPU3	0x08 /* Assert XIR क्रम processor 3	*/
#घोषणा BBC_SXG_RESV	0xf0 /* Reserved			*/

/* POR Source रेजिस्टर.  One may identअगरy the cause of the most recent
 * reset by पढ़ोing this रेजिस्टर.
 */
#घोषणा BBC_PSRC_SPG0	0x0001 /* CPU 0 reset via BBC_SPG रेजिस्टर	*/
#घोषणा BBC_PSRC_SPG1	0x0002 /* CPU 1 reset via BBC_SPG रेजिस्टर	*/
#घोषणा BBC_PSRC_SPG2	0x0004 /* CPU 2 reset via BBC_SPG रेजिस्टर	*/
#घोषणा BBC_PSRC_SPG3	0x0008 /* CPU 3 reset via BBC_SPG रेजिस्टर	*/
#घोषणा BBC_PSRC_SPGSYS	0x0010 /* System reset via BBC_SPG रेजिस्टर	*/
#घोषणा BBC_PSRC_JTAG	0x0020 /* System reset via JTAG+		*/
#घोषणा BBC_PSRC_BUTTON	0x0040 /* System reset via push-button करोngle	*/
#घोषणा BBC_PSRC_PWRUP	0x0080 /* System reset via घातer-up		*/
#घोषणा BBC_PSRC_FE0	0x0100 /* CPU 0 reported Fatal_Error		*/
#घोषणा BBC_PSRC_FE1	0x0200 /* CPU 1 reported Fatal_Error		*/
#घोषणा BBC_PSRC_FE2	0x0400 /* CPU 2 reported Fatal_Error		*/
#घोषणा BBC_PSRC_FE3	0x0800 /* CPU 3 reported Fatal_Error		*/
#घोषणा BBC_PSRC_FE4	0x1000 /* Schizo reported Fatal_Error		*/
#घोषणा BBC_PSRC_FE5	0x2000 /* Safari device 5 reported Fatal_Error	*/
#घोषणा BBC_PSRC_FE6	0x4000 /* CPMS reported Fatal_Error		*/
#घोषणा BBC_PSRC_SYNTH	0x8000 /* System reset when on-board घड़ी synthesizers
				* were updated.
				*/
#घोषणा BBC_PSRC_WDT   0x10000 /* System reset via Super I/O watchकरोg	*/
#घोषणा BBC_PSRC_RSC   0x20000 /* System reset via RSC remote monitoring
				* device
				*/

/* XIR Source रेजिस्टर.  The source of an XIR event sent to a processor may
 * be determined via this रेजिस्टर.
 */
#घोषणा BBC_XSRC_SXG0	0x01	/* CPU 0 received XIR via Soft_XIR_GEN reg */
#घोषणा BBC_XSRC_SXG1	0x02	/* CPU 1 received XIR via Soft_XIR_GEN reg */
#घोषणा BBC_XSRC_SXG2	0x04	/* CPU 2 received XIR via Soft_XIR_GEN reg */
#घोषणा BBC_XSRC_SXG3	0x08	/* CPU 3 received XIR via Soft_XIR_GEN reg */
#घोषणा BBC_XSRC_JTAG	0x10	/* All CPUs received XIR via JTAG+         */
#घोषणा BBC_XSRC_W_OR_B	0x20	/* All CPUs received XIR either because:
				 * a) Super I/O watchकरोg fired, or
				 * b) XIR push button was activated
				 */
#घोषणा BBC_XSRC_RESV	0xc0	/* Reserved				   */

/* Clock Synthesizers Control रेजिस्टर.  This रेजिस्टर provides the big-bang
 * programming पूर्णांकerface to the two घड़ी synthesizers of the machine.
 */
#घोषणा BBC_CSC_SLOAD	0x01	/* Directly connected to S_LOAD pins	*/
#घोषणा BBC_CSC_SDATA	0x02	/* Directly connected to S_DATA pins	*/
#घोषणा BBC_CSC_SCLOCK	0x04	/* Directly connected to S_CLOCK pins	*/
#घोषणा BBC_CSC_RESV	0x78	/* Reserved				*/
#घोषणा BBC_CSC_RST	0x80	/* Generate प्रणाली reset when S_LOAD==1	*/

/* Energy Star Control रेजिस्टर.  This रेजिस्टर is used to generate the
 * घड़ी frequency change trigger to the मुख्य प्रणाली devices (Schizo and
 * the processors).  The transition occurs when bits in this रेजिस्टर
 * go from 0 to 1, only one bit must be set at once अन्यथा no action
 * occurs.  Basically the sequence of events is:
 * a) Choose new frequency: full, 1/2 or 1/32
 * b) Program this desired frequency पूर्णांकo the cpus and Schizo.
 * c) Set the same value in this रेजिस्टर.
 * d) 16 प्रणाली घड़ीs later, clear this रेजिस्टर.
 */
#घोषणा BBC_ES_CTRL_1_1		0x01	/* Full frequency	*/
#घोषणा BBC_ES_CTRL_1_2		0x02	/* 1/2 frequency	*/
#घोषणा BBC_ES_CTRL_1_32	0x20	/* 1/32 frequency	*/
#घोषणा BBC_ES_RESV		0xdc	/* Reserved		*/

/* Energy Star Assert Change Time रेजिस्टर.  This determines the number
 * of BBC घड़ी cycles (which is half the प्रणाली frequency) between
 * the detection of FREEZE_ACK being निश्चितed and the निश्चितion of
 * the CLK_CHANGE_L[2:0] संकेतs.
 */
#घोषणा BBC_ES_ACT_VAL	0xff

/* Energy Star Assert Bypass Time रेजिस्टर.  This determines the number
 * of BBC घड़ी cycles (which is half the प्रणाली frequency) between
 * the निश्चितion of the CLK_CHANGE_L[2:0] संकेतs and the निश्चितion of
 * the ESTAR_PLL_BYPASS संकेत.
 */
#घोषणा BBC_ES_ABT_VAL	0xffff

/* Energy Star PLL Settle Time रेजिस्टर.  This determines the number of
 * BBC घड़ी cycles (which is half the प्रणाली frequency) between the
 * de-निश्चितion of CLK_CHANGE_L[2:0] and the de-निश्चितion of the FREEZE_L
 * संकेत.
 */
#घोषणा BBC_ES_PST_VAL	0xffffffff

/* Energy Star Frequency Switch Latency रेजिस्टर.  This is the number of
 * BBC घड़ीs between the de-निश्चितion of CLK_CHANGE_L[2:0] and the first
 * edge of the Safari घड़ी at the new frequency.
 */
#घोषणा BBC_ES_FSL_VAL	0xffffffff

/* Keyboard Beep control रेजिस्टर.  This is a simple enabler क्रम the audio
 * beep sound.
 */
#घोषणा BBC_KBD_BEEP_ENABLE	0x01 /* Enable beep	*/
#घोषणा BBC_KBD_BEEP_RESV	0xfe /* Reserved	*/

/* Keyboard Beep Counter रेजिस्टर.  There is a मुक्त-running counter inside
 * the BBC which runs at half the प्रणाली घड़ी.  The bit set in this रेजिस्टर
 * determines when the audio sound is generated.  So क्रम example अगर bit
 * 10 is set, the audio beep will oscillate at 1/(2**12).  The keyboard beep
 * generator स्वतःmatically selects a dअगरferent bit to use अगर the प्रणाली घड़ी
 * is changed via Energy Star.
 */
#घोषणा BBC_KBD_BCNT_BITS	0x0007fc00
#घोषणा BBC_KBC_BCNT_RESV	0xfff803ff

#पूर्ण_अगर /* _SPARC64_BBC_H */

