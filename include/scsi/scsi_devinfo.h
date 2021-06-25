<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_DEVINFO_H
#घोषणा _SCSI_SCSI_DEVINFO_H
/*
 * Flags क्रम SCSI devices that need special treaपंचांगent
 */

/* Only scan LUN 0 */
#घोषणा BLIST_NOLUN		((__क्रमce blist_flags_t)(1ULL << 0))
/* Known to have LUNs, क्रमce scanning.
 * DEPRECATED: Use max_luns=N */
#घोषणा BLIST_FORCELUN		((__क्रमce blist_flags_t)(1ULL << 1))
/* Flag क्रम broken handshaking */
#घोषणा BLIST_BORKEN		((__क्रमce blist_flags_t)(1ULL << 2))
/* unlock by special command */
#घोषणा BLIST_KEY		((__क्रमce blist_flags_t)(1ULL << 3))
/* Do not use LUNs in parallel */
#घोषणा BLIST_SINGLELUN		((__क्रमce blist_flags_t)(1ULL << 4))
/* Buggy Tagged Command Queuing */
#घोषणा BLIST_NOTQ		((__क्रमce blist_flags_t)(1ULL << 5))
/* Non consecutive LUN numbering */
#घोषणा BLIST_SPARSELUN		((__क्रमce blist_flags_t)(1ULL << 6))
/* Aव्योम LUNS >= 5 */
#घोषणा BLIST_MAX5LUN		((__क्रमce blist_flags_t)(1ULL << 7))
/* Treat as (removable) CD-ROM */
#घोषणा BLIST_ISROM		((__क्रमce blist_flags_t)(1ULL << 8))
/* LUNs past 7 on a SCSI-2 device */
#घोषणा BLIST_LARGELUN		((__क्रमce blist_flags_t)(1ULL << 9))
/* override additional length field */
#घोषणा BLIST_INQUIRY_36	((__क्रमce blist_flags_t)(1ULL << 10))
#घोषणा __BLIST_UNUSED_11	((__क्रमce blist_flags_t)(1ULL << 11))
/* करो not करो स्वतःmatic start on add */
#घोषणा BLIST_NOSTARTONADD	((__क्रमce blist_flags_t)(1ULL << 12))
#घोषणा __BLIST_UNUSED_13	((__क्रमce blist_flags_t)(1ULL << 13))
#घोषणा __BLIST_UNUSED_14	((__क्रमce blist_flags_t)(1ULL << 14))
#घोषणा __BLIST_UNUSED_15	((__क्रमce blist_flags_t)(1ULL << 15))
#घोषणा __BLIST_UNUSED_16	((__क्रमce blist_flags_t)(1ULL << 16))
/* try REPORT_LUNS even क्रम SCSI-2 devs (अगर HBA supports more than 8 LUNs) */
#घोषणा BLIST_REPORTLUN2	((__क्रमce blist_flags_t)(1ULL << 17))
/* करोn't try REPORT_LUNS scan (SCSI-3 devs) */
#घोषणा BLIST_NOREPORTLUN	((__क्रमce blist_flags_t)(1ULL << 18))
/* करोn't use PREVENT-ALLOW commands */
#घोषणा BLIST_NOT_LOCKABLE	((__क्रमce blist_flags_t)(1ULL << 19))
/* device is actually क्रम RAID config */
#घोषणा BLIST_NO_ULD_ATTACH	((__क्रमce blist_flags_t)(1ULL << 20))
/* select without ATN */
#घोषणा BLIST_SELECT_NO_ATN	((__क्रमce blist_flags_t)(1ULL << 21))
/* retry HARDWARE_ERROR */
#घोषणा BLIST_RETRY_HWERROR	((__क्रमce blist_flags_t)(1ULL << 22))
/* maximum 512 sector cdb length */
#घोषणा BLIST_MAX_512		((__क्रमce blist_flags_t)(1ULL << 23))
#घोषणा __BLIST_UNUSED_24	((__क्रमce blist_flags_t)(1ULL << 24))
/* Disable T10 PI (DIF) */
#घोषणा BLIST_NO_DIF		((__क्रमce blist_flags_t)(1ULL << 25))
/* Ignore SBC-3 VPD pages */
#घोषणा BLIST_SKIP_VPD_PAGES	((__क्रमce blist_flags_t)(1ULL << 26))
#घोषणा __BLIST_UNUSED_27	((__क्रमce blist_flags_t)(1ULL << 27))
/* Attempt to पढ़ो VPD pages */
#घोषणा BLIST_TRY_VPD_PAGES	((__क्रमce blist_flags_t)(1ULL << 28))
/* करोn't try to issue RSOC */
#घोषणा BLIST_NO_RSOC		((__क्रमce blist_flags_t)(1ULL << 29))
/* maximum 1024 sector cdb length */
#घोषणा BLIST_MAX_1024		((__क्रमce blist_flags_t)(1ULL << 30))
/* Use UNMAP limit क्रम WRITE SAME */
#घोषणा BLIST_UNMAP_LIMIT_WS	((__क्रमce blist_flags_t)(1ULL << 31))
/* Always retry ABORTED_COMMAND with Internal Target Failure */
#घोषणा BLIST_RETRY_ITF		((__क्रमce blist_flags_t)(1ULL << 32))
/* Always retry ABORTED_COMMAND with ASC 0xc1 */
#घोषणा BLIST_RETRY_ASC_C1	((__क्रमce blist_flags_t)(1ULL << 33))

#घोषणा __BLIST_LAST_USED BLIST_RETRY_ASC_C1

#घोषणा __BLIST_HIGH_UNUSED (~(__BLIST_LAST_USED | \
			       (__क्रमce blist_flags_t) \
			       ((__क्रमce __u64)__BLIST_LAST_USED - 1ULL)))
#घोषणा __BLIST_UNUSED_MASK (__BLIST_UNUSED_11 | \
			     __BLIST_UNUSED_13 | \
			     __BLIST_UNUSED_14 | \
			     __BLIST_UNUSED_15 | \
			     __BLIST_UNUSED_16 | \
			     __BLIST_UNUSED_24 | \
			     __BLIST_UNUSED_27 | \
			     __BLIST_HIGH_UNUSED)

#पूर्ण_अगर
