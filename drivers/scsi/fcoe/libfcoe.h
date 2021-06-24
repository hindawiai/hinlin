<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FCOE_LIBFCOE_H_
#घोषणा _FCOE_LIBFCOE_H_

बाह्य अचिन्हित पूर्णांक libfcoe_debug_logging;
#घोषणा LIBFCOE_LOGGING	          0x01 /* General logging, not categorized */
#घोषणा LIBFCOE_FIP_LOGGING       0x02 /* FIP logging */
#घोषणा LIBFCOE_TRANSPORT_LOGGING 0x04 /* FCoE transport logging */
#घोषणा LIBFCOE_SYSFS_LOGGING     0x08 /* fcoe_sysfs logging */

#घोषणा LIBFCOE_CHECK_LOGGING(LEVEL, CMD)		\
करो अणु							\
	अगर (unlikely(libfcoe_debug_logging & LEVEL))	\
		करो अणु					\
			CMD;				\
		पूर्ण जबतक (0);				\
पूर्ण जबतक (0)

#घोषणा LIBFCOE_DBG(fmt, args...)					\
	LIBFCOE_CHECK_LOGGING(LIBFCOE_LOGGING,				\
			      pr_info("libfcoe: " fmt, ##args);)

#घोषणा LIBFCOE_FIP_DBG(fip, fmt, args...)				\
	LIBFCOE_CHECK_LOGGING(LIBFCOE_FIP_LOGGING,			\
			      pr_info("host%d: fip: " fmt,		\
				      (fip)->lp->host->host_no, ##args);)

#घोषणा LIBFCOE_TRANSPORT_DBG(fmt, args...)				\
	LIBFCOE_CHECK_LOGGING(LIBFCOE_TRANSPORT_LOGGING,		\
			      pr_info("%s: " fmt, __func__, ##args);)

#घोषणा LIBFCOE_SYSFS_DBG(cdev, fmt, args...)				\
	LIBFCOE_CHECK_LOGGING(LIBFCOE_SYSFS_LOGGING,			\
			      pr_info("ctlr_%d: " fmt, cdev->id, ##args);)

#पूर्ण_अगर /* _FCOE_LIBFCOE_H_ */
