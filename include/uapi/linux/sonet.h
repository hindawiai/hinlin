<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* sonet.h - SONET/SHD physical layer control */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 

#अगर_अघोषित _UAPILINUX_SONET_H
#घोषणा _UAPILINUX_SONET_H

#घोषणा __SONET_ITEMS \
    __HANDLE_ITEM(section_bip); 	/* section parity errors (B1) */ \
    __HANDLE_ITEM(line_bip);		/* line parity errors (B2) */ \
    __HANDLE_ITEM(path_bip);		/* path parity errors (B3) */ \
    __HANDLE_ITEM(line_febe);		/* line parity errors at remote */ \
    __HANDLE_ITEM(path_febe);		/* path parity errors at remote */ \
    __HANDLE_ITEM(corr_hcs);		/* correctable header errors */ \
    __HANDLE_ITEM(uncorr_hcs);		/* uncorrectable header errors */ \
    __HANDLE_ITEM(tx_cells);		/* cells sent */ \
    __HANDLE_ITEM(rx_cells);		/* cells received */

काष्ठा sonet_stats अणु
#घोषणा __HANDLE_ITEM(i) पूर्णांक i
	__SONET_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण __attribute__ ((packed));


#घोषणा SONET_GETSTAT	_IOR('a',ATMIOC_PHYTYP,काष्ठा sonet_stats)
					/* get statistics */
#घोषणा SONET_GETSTATZ	_IOR('a',ATMIOC_PHYTYP+1,काष्ठा sonet_stats)
					/* ... and zero counters */
#घोषणा SONET_SETDIAG	_IOWR('a',ATMIOC_PHYTYP+2,पूर्णांक)
					/* set error insertion */
#घोषणा SONET_CLRDIAG	_IOWR('a',ATMIOC_PHYTYP+3,पूर्णांक)
					/* clear error insertion */
#घोषणा SONET_GETDIAG	_IOR('a',ATMIOC_PHYTYP+4,पूर्णांक)
					/* query error insertion */
#घोषणा SONET_SETFRAMING _IOW('a',ATMIOC_PHYTYP+5,पूर्णांक)
					/* set framing mode (SONET/SDH) */
#घोषणा SONET_GETFRAMING _IOR('a',ATMIOC_PHYTYP+6,पूर्णांक)
					/* get framing mode */
#घोषणा SONET_GETFRSENSE _IOR('a',ATMIOC_PHYTYP+7, \
  अचिन्हित अक्षर[SONET_FRSENSE_SIZE])	/* get framing sense inक्रमmation */

#घोषणा SONET_INS_SBIP	  1		/* section BIP */
#घोषणा SONET_INS_LBIP	  2		/* line BIP */
#घोषणा SONET_INS_PBIP	  4		/* path BIP */
#घोषणा SONET_INS_FRAME	  8		/* out of frame */
#घोषणा SONET_INS_LOS	 16		/* set line to zero */
#घोषणा SONET_INS_LAIS	 32		/* line alarm indication संकेत */
#घोषणा SONET_INS_PAIS	 64		/* path alarm indication संकेत */
#घोषणा SONET_INS_HCS	128		/* insert HCS error */

#घोषणा SONET_FRAME_SONET 0		/* SONET STS-3 framing */
#घोषणा SONET_FRAME_SDH   1		/* SDH STM-1 framing */

#घोषणा SONET_FRSENSE_SIZE 6		/* C1[3],H1[3] (0xff क्रम unknown) */



#पूर्ण_अगर /* _UAPILINUX_SONET_H */
