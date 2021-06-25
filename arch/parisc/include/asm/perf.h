<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PERF_H_
#घोषणा _ASM_PERF_H_

/* ioctls */
#घोषणा PA_PERF_ON	_IO('p', 1)
#घोषणा PA_PERF_OFF	_IOR('p', 2, अचिन्हित पूर्णांक)
#घोषणा PA_PERF_VERSION	_IOR('p', 3, पूर्णांक)

#घोषणा PA_PERF_DEV	"perf"
#घोषणा PA_PERF_MINOR	146

/* Interface types */
#घोषणा UNKNOWN_INTF    255
#घोषणा ONYX_INTF         0
#घोषणा CUDA_INTF         1

/* Common Onyx and Cuda images */
#घोषणा CPI                 0
#घोषणा BUSUTIL             1
#घोषणा TLBMISS             2
#घोषणा TLBHANDMISS         3
#घोषणा PTKN                4
#घोषणा PNTKN               5
#घोषणा IMISS               6
#घोषणा DMISS               7
#घोषणा DMISS_ACCESS        8 
#घोषणा BIG_CPI 	    9
#घोषणा BIG_LS		   10  
#घोषणा BR_ABORT	   11
#घोषणा ISNT		   12 
#घोषणा QUADRANT           13
#घोषणा RW_PDFET           14
#घोषणा RW_WDFET           15
#घोषणा SHLIB_CPI          16

/* Cuda only Images */
#घोषणा FLOPS              17
#घोषणा CACHEMISS          18 
#घोषणा BRANCHES           19             
#घोषणा CRSTACK            20 
#घोषणा I_CACHE_SPEC       21 
#घोषणा MAX_CUDA_IMAGES    22 

/* Onyx only Images */
#घोषणा ADDR_INV_ABORT_ALU 17
#घोषणा BRAD_STALL	   18 
#घोषणा CNTL_IN_PIPEL	   19 
#घोषणा DSNT_XFH	   20 
#घोषणा FET_SIG1	   21 
#घोषणा FET_SIG2	   22 
#घोषणा G7_1		   23 
#घोषणा G7_2		   24 
#घोषणा G7_3 		   25
#घोषणा G7_4		   26
#घोषणा MPB_LABORT         27
#घोषणा PANIC              28
#घोषणा RARE_INST          29 
#घोषणा RW_DFET            30 
#घोषणा RW_IFET            31 
#घोषणा RW_SDFET           32 
#घोषणा SPEC_IFET          33 
#घोषणा ST_COND0           34 
#घोषणा ST_COND1           35 
#घोषणा ST_COND2           36
#घोषणा ST_COND3           37
#घोषणा ST_COND4           38
#घोषणा ST_UNPRED0         39 
#घोषणा ST_UNPRED1         40 
#घोषणा UNPRED             41 
#घोषणा GO_STORE           42
#घोषणा SHLIB_CALL         43
#घोषणा MAX_ONYX_IMAGES    44

#पूर्ण_अगर
