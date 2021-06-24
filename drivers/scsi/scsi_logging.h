<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_LOGGING_H
#घोषणा _SCSI_LOGGING_H


/*
 * This defines the scsi logging feature.  It is a means by which the user can
 * select how much inक्रमmation they get about various goings on, and it can be
 * really useful क्रम fault tracing.  The logging word is भागided पूर्णांकo 10 3-bit
 * bitfields, each of which describes a loglevel.  The भागision of things is
 * somewhat arbitrary, and the भागision of the word could be changed अगर it
 * were really needed क्रम any reason.  The numbers below are the only place
 * where these are specअगरied.  For a first go-around, 3 bits is more than
 * enough, since this gives 8 levels of logging (really 7, since 0 is always
 * off).  Cutting to 2 bits might be wise at some poपूर्णांक.
 */

#घोषणा SCSI_LOG_ERROR_SHIFT              0
#घोषणा SCSI_LOG_TIMEOUT_SHIFT            3
#घोषणा SCSI_LOG_SCAN_SHIFT               6
#घोषणा SCSI_LOG_MLQUEUE_SHIFT            9
#घोषणा SCSI_LOG_MLCOMPLETE_SHIFT         12
#घोषणा SCSI_LOG_LLQUEUE_SHIFT            15
#घोषणा SCSI_LOG_LLCOMPLETE_SHIFT         18
#घोषणा SCSI_LOG_HLQUEUE_SHIFT            21
#घोषणा SCSI_LOG_HLCOMPLETE_SHIFT         24
#घोषणा SCSI_LOG_IOCTL_SHIFT              27

#घोषणा SCSI_LOG_ERROR_BITS               3
#घोषणा SCSI_LOG_TIMEOUT_BITS             3
#घोषणा SCSI_LOG_SCAN_BITS                3
#घोषणा SCSI_LOG_MLQUEUE_BITS             3
#घोषणा SCSI_LOG_MLCOMPLETE_BITS          3
#घोषणा SCSI_LOG_LLQUEUE_BITS             3
#घोषणा SCSI_LOG_LLCOMPLETE_BITS          3
#घोषणा SCSI_LOG_HLQUEUE_BITS             3
#घोषणा SCSI_LOG_HLCOMPLETE_BITS          3
#घोषणा SCSI_LOG_IOCTL_BITS               3

बाह्य अचिन्हित पूर्णांक scsi_logging_level;

#अगर_घोषित CONFIG_SCSI_LOGGING

#घोषणा SCSI_LOG_LEVEL(SHIFT, BITS)				\
        ((scsi_logging_level >> (SHIFT)) & ((1 << (BITS)) - 1))

#घोषणा SCSI_CHECK_LOGGING(SHIFT, BITS, LEVEL, CMD)		\
करो अणु								\
        अगर (unlikely((SCSI_LOG_LEVEL(SHIFT, BITS)) > (LEVEL)))	\
		करो अणु						\
			CMD;					\
		पूर्ण जबतक (0);					\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा SCSI_LOG_LEVEL(SHIFT, BITS) 0
#घोषणा SCSI_CHECK_LOGGING(SHIFT, BITS, LEVEL, CMD) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SCSI_LOGGING */

/*
 * These are the macros that are actually used throughout the code to
 * log events.  If logging isn't enabled, they are no-ops and will be
 * completely असलent from the user's code.
 */
#घोषणा SCSI_LOG_ERROR_RECOVERY(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_ERROR_SHIFT, SCSI_LOG_ERROR_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_TIMEOUT(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_TIMEOUT_SHIFT, SCSI_LOG_TIMEOUT_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_SCAN_BUS(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_SCAN_SHIFT, SCSI_LOG_SCAN_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_MLQUEUE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_MLQUEUE_SHIFT, SCSI_LOG_MLQUEUE_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_MLCOMPLETE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_MLCOMPLETE_SHIFT, SCSI_LOG_MLCOMPLETE_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_LLQUEUE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_LLQUEUE_SHIFT, SCSI_LOG_LLQUEUE_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_LLCOMPLETE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_LLCOMPLETE_SHIFT, SCSI_LOG_LLCOMPLETE_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_HLQUEUE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_HLQUEUE_SHIFT, SCSI_LOG_HLQUEUE_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_HLCOMPLETE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_HLCOMPLETE_SHIFT, SCSI_LOG_HLCOMPLETE_BITS, LEVEL,CMD);
#घोषणा SCSI_LOG_IOCTL(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_IOCTL_SHIFT, SCSI_LOG_IOCTL_BITS, LEVEL,CMD);

#पूर्ण_अगर /* _SCSI_LOGGING_H */
