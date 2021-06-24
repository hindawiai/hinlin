<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/drivers/message/fusion/mptdebug.h
 *      For use with LSI PCI chip/adapter(s)
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 1999-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#अगर_अघोषित MPTDEBUG_H_INCLUDED
#घोषणा MPTDEBUG_H_INCLUDED

/*
 * debug level can be programmed on the fly via SysFS (hex values)
 *
 * Example:  (programming क्रम MPT_DEBUG_EVENTS on host 5)
 *
 * echo 8 > /sys/class/scsi_host/host5/debug_level
 *
 * --------------------------------------------------------
 * mpt_debug_level - command line parameter
 * this allow enabling debug at driver load समय (क्रम all iocs)
 *
 * Example  (programming क्रम MPT_DEBUG_EVENTS)
 *
 * insmod mptbase.ko mpt_debug_level=8
 *
 * --------------------------------------------------------
 * CONFIG_FUSION_LOGGING - enables compiling debug पूर्णांकo driver
 * this can be enabled in the driver Makefile
 *
 *
 * --------------------------------------------------------
 * Please note most debug prपूर्णांकs are set to logging priority = debug
 * This is the lowest level, and most verbose.  Please refer to manual
 * pages क्रम syslogd or syslogd-ng on how to configure this.
 */

#घोषणा MPT_DEBUG			0x00000001
#घोषणा MPT_DEBUG_MSG_FRAME		0x00000002
#घोषणा MPT_DEBUG_SG			0x00000004
#घोषणा MPT_DEBUG_EVENTS		0x00000008
#घोषणा MPT_DEBUG_VERBOSE_EVENTS	0x00000010
#घोषणा MPT_DEBUG_INIT			0x00000020
#घोषणा MPT_DEBUG_EXIT			0x00000040
#घोषणा MPT_DEBUG_FAIL			0x00000080
#घोषणा MPT_DEBUG_TM			0x00000100
#घोषणा MPT_DEBUG_DV			0x00000200
#घोषणा MPT_DEBUG_REPLY			0x00000400
#घोषणा MPT_DEBUG_HANDSHAKE		0x00000800
#घोषणा MPT_DEBUG_CONFIG		0x00001000
#घोषणा MPT_DEBUG_DL			0x00002000
#घोषणा MPT_DEBUG_RESET			0x00008000
#घोषणा MPT_DEBUG_SCSI			0x00010000
#घोषणा MPT_DEBUG_IOCTL			0x00020000
#घोषणा MPT_DEBUG_FC			0x00080000
#घोषणा MPT_DEBUG_SAS			0x00100000
#घोषणा MPT_DEBUG_SAS_WIDE		0x00200000
#घोषणा MPT_DEBUG_36GB_MEM              0x00400000

/*
 * CONFIG_FUSION_LOGGING - enabled in Kconfig
 */

#अगर_घोषित CONFIG_FUSION_LOGGING
#घोषणा MPT_CHECK_LOGGING(IOC, CMD, BITS)			\
करो अणु								\
	अगर (IOC->debug_level & BITS)				\
		CMD;						\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा MPT_CHECK_LOGGING(IOC, CMD, BITS)			\
करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर


/*
 * debug macros
 */

#घोषणा dprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG)

#घोषणा dsgprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SG)

#घोषणा devtprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_EVENTS)

#घोषणा devtverboseprपूर्णांकk(IOC, CMD)		\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_VERBOSE_EVENTS)

#घोषणा dinitprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_INIT)

#घोषणा dनिकासprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_EXIT)

#घोषणा dfailprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_FAIL)

#घोषणा dपंचांगprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_TM)

#घोषणा ddvprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_DV)

#घोषणा dreplyprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_REPLY)

#घोषणा dhsprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_HANDSHAKE)

#घोषणा dcprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_CONFIG)

#घोषणा ddlprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_DL)

#घोषणा drsprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_RESET)

#घोषणा dsprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SCSI)

#घोषणा dctlprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_IOCTL)

#घोषणा dfcprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_FC)

#घोषणा dsasprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SAS)

#घोषणा dsaswideprपूर्णांकk(IOC, CMD)		\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SAS_WIDE)

#घोषणा d36memprपूर्णांकk(IOC, CMD)		\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_36GB_MEM)


/*
 * Verbose logging
 */
#अगर defined(MPT_DEBUG_VERBOSE) && defined(CONFIG_FUSION_LOGGING)
अटल अंतरभूत व्योम
DBG_DUMP_FW_DOWNLOAD(MPT_ADAPTER *ioc, u32  *mfp, पूर्णांक numfrags)
अणु
	पूर्णांक i;

	अगर (!(ioc->debug_level & MPT_DEBUG))
		वापस;
	prपूर्णांकk(KERN_DEBUG "F/W download request:\n");
	क्रम (i=0; i < 7+numfrags*2; i++)
		prपूर्णांकk(" %08x", le32_to_cpu(mfp[i]));
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_PUT_MSG_FRAME(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक	 ii, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_MSG_FRAME))
		वापस;
	prपूर्णांकk(KERN_DEBUG "%s: About to Put msg frame @ %p:\n",
		ioc->name, mfp);
	n = ioc->req_sz/4 - 1;
	जबतक (mfp[n] == 0)
		n--;
	क्रम (ii=0; ii<=n; ii++) अणु
		अगर (ii && ((ii%8)==0))
			prपूर्णांकk("\n");
		prपूर्णांकk(" %08x", le32_to_cpu(mfp[ii]));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_FW_REQUEST_FRAME(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक  i, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_MSG_FRAME))
		वापस;
	n = 10;
	prपूर्णांकk(KERN_INFO " ");
	क्रम (i = 0; i < n; i++)
		prपूर्णांकk(" %08x", le32_to_cpu(mfp[i]));
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_REQUEST_FRAME(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक  i, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_MSG_FRAME))
		वापस;
	n = 24;
	क्रम (i=0; i<n; i++) अणु
		अगर (i && ((i%8)==0))
			prपूर्णांकk("\n");
		prपूर्णांकk("%08x ", le32_to_cpu(mfp[i]));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_REPLY_FRAME(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक  i, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_MSG_FRAME))
		वापस;
	n = (le32_to_cpu(mfp[0]) & 0x00FF0000) >> 16;
	prपूर्णांकk(KERN_INFO " ");
	क्रम (i=0; i<n; i++)
		prपूर्णांकk(" %08x", le32_to_cpu(mfp[i]));
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_REQUEST_FRAME_HDR(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक  i, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_MSG_FRAME))
		वापस;
	n = 3;
	prपूर्णांकk(KERN_INFO " ");
	क्रम (i=0; i<n; i++)
		prपूर्णांकk(" %08x", le32_to_cpu(mfp[i]));
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_TM_REQUEST_FRAME(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक  i, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_TM))
		वापस;
	n = 13;
	prपूर्णांकk(KERN_DEBUG "TM_REQUEST:\n");
	क्रम (i=0; i<n; i++) अणु
		अगर (i && ((i%8)==0))
			prपूर्णांकk("\n");
		prपूर्णांकk("%08x ", le32_to_cpu(mfp[i]));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल अंतरभूत व्योम
DBG_DUMP_TM_REPLY_FRAME(MPT_ADAPTER *ioc, u32 *mfp)
अणु
	पूर्णांक  i, n;

	अगर (!(ioc->debug_level & MPT_DEBUG_TM))
		वापस;
	n = (le32_to_cpu(mfp[0]) & 0x00FF0000) >> 16;
	prपूर्णांकk(KERN_DEBUG "TM_REPLY MessageLength=%d:\n", n);
	क्रम (i=0; i<n; i++) अणु
		अगर (i && ((i%8)==0))
			prपूर्णांकk("\n");
		prपूर्णांकk(" %08x", le32_to_cpu(mfp[i]));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

#घोषणा dmfprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_MSG_FRAME)

# अन्यथा /* अगरdef MPT_DEBUG_MF */

#घोषणा DBG_DUMP_FW_DOWNLOAD(IOC, mfp, numfrags)
#घोषणा DBG_DUMP_PUT_MSG_FRAME(IOC, mfp)
#घोषणा DBG_DUMP_FW_REQUEST_FRAME(IOC, mfp)
#घोषणा DBG_DUMP_REQUEST_FRAME(IOC, mfp)
#घोषणा DBG_DUMP_REPLY_FRAME(IOC, mfp)
#घोषणा DBG_DUMP_REQUEST_FRAME_HDR(IOC, mfp)
#घोषणा DBG_DUMP_TM_REQUEST_FRAME(IOC, mfp)
#घोषणा DBG_DUMP_TM_REPLY_FRAME(IOC, mfp)

#घोषणा dmfprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_MSG_FRAME)

#पूर्ण_अगर /* defined(MPT_DEBUG_VERBOSE) && defined(CONFIG_FUSION_LOGGING) */

#पूर्ण_अगर /* अगरndef MPTDEBUG_H_INCLUDED */
