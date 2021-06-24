<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BCM963XX_TAG_H__
#घोषणा __LINUX_BCM963XX_TAG_H__

#समावेश <linux/types.h>

#घोषणा TAGVER_LEN		4	/* Length of Tag Version */
#घोषणा TAGLAYOUT_LEN		4	/* Length of FlashLayoutVer */
#घोषणा SIG1_LEN		20	/* Company Signature 1 Length */
#घोषणा SIG2_LEN		14	/* Company Signature 2 Length */
#घोषणा BOARDID_LEN		16	/* Length of BoardId */
#घोषणा ENDIANFLAG_LEN		2	/* Endian Flag Length */
#घोषणा CHIPID_LEN		6	/* Chip Id Length */
#घोषणा IMAGE_LEN		10	/* Length of Length Field */
#घोषणा ADDRESS_LEN		12	/* Length of Address field */
#घोषणा IMAGE_SEQUENCE_LEN	4	/* Image sequence Length */
#घोषणा RSASIG_LEN		20	/* Length of RSA Signature in tag */
#घोषणा TAGINFO1_LEN		30	/* Length of venकरोr inक्रमmation field1 in tag */
#घोषणा FLASHLAYOUTVER_LEN	4	/* Length of Flash Layout Version String tag */
#घोषणा TAGINFO2_LEN		16	/* Length of venकरोr inक्रमmation field2 in tag */
#घोषणा ALTTAGINFO_LEN		54	/* Alternate length क्रम venकरोr inक्रमmation; Pirelli */

#घोषणा NUM_PIRELLI		2
#घोषणा IMAGETAG_CRC_START	0xFFFFFFFF

#घोषणा PIRELLI_BOARDS अणु \
	"AGPF-S0", \
	"DWV-S0", \
पूर्ण

/* Extended flash address, needs to be subtracted
 * from bcm_tag flash image offsets.
 */
#घोषणा BCM963XX_EXTENDED_SIZE	0xBFC00000

/*
 * The broadcom firmware assumes the rootfs starts the image,
 * thereक्रमe uses the rootfs start (flash_image_address)
 * to determine where to flash the image.  Since we have the kernel first
 * we have to give it the kernel address, but the crc uses the length
 * associated with this address (root_length), which is added to the kernel
 * length (kernel_length) to determine the length of image to flash and thus
 * needs to be rootfs + deadcode (jffs2 खातापूर्ण marker)
*/

काष्ठा bcm_tag अणु
	/* 0-3: Version of the image tag */
	अक्षर tag_version[TAGVER_LEN];
	/* 4-23: Company Line 1 */
	अक्षर sig_1[SIG1_LEN];
	/*  24-37: Company Line 2 */
	अक्षर sig_2[SIG2_LEN];
	/* 38-43: Chip this image is क्रम */
	अक्षर chip_id[CHIPID_LEN];
	/* 44-59: Board name */
	अक्षर board_id[BOARDID_LEN];
	/* 60-61: Map endianness -- 1 BE 0 LE */
	अक्षर big_endian[ENDIANFLAG_LEN];
	/* 62-71: Total length of image */
	अक्षर total_length[IMAGE_LEN];
	/* 72-83: Address in memory of CFE */
	अक्षर cfe__address[ADDRESS_LEN];
	/* 84-93: Size of CFE */
	अक्षर cfe_length[IMAGE_LEN];
	/* 94-105: Address in memory of image start
	 * (kernel क्रम OpenWRT, rootfs क्रम stock firmware)
	 */
	अक्षर flash_image_start[ADDRESS_LEN];
	/* 106-115: Size of rootfs */
	अक्षर root_length[IMAGE_LEN];
	/* 116-127: Address in memory of kernel */
	अक्षर kernel_address[ADDRESS_LEN];
	/* 128-137: Size of kernel */
	अक्षर kernel_length[IMAGE_LEN];
	/* 138-141: Image sequence number
	 * (to be incremented when flashed with a new image)
	 */
	अक्षर image_sequence[IMAGE_SEQUENCE_LEN];
	/* 142-161: RSA Signature (not used; some venकरोrs may use this) */
	अक्षर rsa_signature[RSASIG_LEN];
	/* 162-191: Compilation and related inक्रमmation (not used in OpenWrt) */
	अक्षर inक्रमmation1[TAGINFO1_LEN];
	/* 192-195: Version flash layout */
	अक्षर flash_layout_ver[FLASHLAYOUTVER_LEN];
	/* 196-199: kernel+rootfs CRC32 */
	__u32 fskernel_crc;
	/* 200-215: Unused except on Alice Gate where it is inक्रमmation */
	अक्षर inक्रमmation2[TAGINFO2_LEN];
	/* 216-219: CRC32 of image less imagetag (kernel क्रम Alice Gate) */
	__u32 image_crc;
	/* 220-223: CRC32 of rootfs partition */
	__u32 rootfs_crc;
	/* 224-227: CRC32 of kernel partition */
	__u32 kernel_crc;
	/* 228-235: Unused at present */
	अक्षर reserved1[8];
	/* 236-239: CRC32 of header excluding last 20 bytes */
	__u32 header_crc;
	/* 240-255: Unused at present */
	अक्षर reserved2[16];
पूर्ण;

#पूर्ण_अगर /* __LINUX_BCM63XX_TAG_H__ */
