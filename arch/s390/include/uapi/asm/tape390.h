<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*************************************************************************
 *
 *	   enables user programs to display messages and control encryption
 *	   on s390 tape devices
 *
 *	   Copyright IBM Corp. 2001, 2006
 *	   Author(s): Michael Holzheu <holzheu@de.ibm.com>
 *
 *************************************************************************/

#अगर_अघोषित _TAPE390_H
#घोषणा _TAPE390_H

#घोषणा TAPE390_DISPLAY _IOW('d', 1, काष्ठा display_काष्ठा)

/*
 * The TAPE390_DISPLAY ioctl calls the Load Display command
 * which transfers 17 bytes of data from the channel to the subप्रणाली:
 *     - 1 क्रमmat control byte, and
 *     - two 8-byte messages
 *
 * Format control byte:
 *   0-2: New Message Overlay
 *     3: Alternate Messages
 *     4: Blink Message
 *     5: Display Low/High Message
 *     6: Reserved
 *     7: Automatic Load Request
 *
 */

प्रकार काष्ठा display_काष्ठा अणु
        अक्षर cntrl;
        अक्षर message1[8];
        अक्षर message2[8];
पूर्ण display_काष्ठा;

/*
 * Tape encryption support
 */

काष्ठा tape390_crypt_info अणु
	अक्षर capability;
	अक्षर status;
	अक्षर medium_status;
पूर्ण __attribute__ ((packed));


/* Macros क्रम "capable" field */
#घोषणा TAPE390_CRYPT_SUPPORTED_MASK 0x01
#घोषणा TAPE390_CRYPT_SUPPORTED(x) \
	((x.capability & TAPE390_CRYPT_SUPPORTED_MASK))

/* Macros क्रम "status" field */
#घोषणा TAPE390_CRYPT_ON_MASK 0x01
#घोषणा TAPE390_CRYPT_ON(x) (((x.status) & TAPE390_CRYPT_ON_MASK))

/* Macros क्रम "medium status" field */
#घोषणा TAPE390_MEDIUM_LOADED_MASK 0x01
#घोषणा TAPE390_MEDIUM_ENCRYPTED_MASK 0x02
#घोषणा TAPE390_MEDIUM_ENCRYPTED(x) \
	(((x.medium_status) & TAPE390_MEDIUM_ENCRYPTED_MASK))
#घोषणा TAPE390_MEDIUM_LOADED(x) \
	(((x.medium_status) & TAPE390_MEDIUM_LOADED_MASK))

/*
 * The TAPE390_CRYPT_SET ioctl is used to चयन on/off encryption.
 * The "encryption_capable" and "tape_status" fields are ignored क्रम this ioctl!
 */
#घोषणा TAPE390_CRYPT_SET _IOW('d', 2, काष्ठा tape390_crypt_info)

/*
 * The TAPE390_CRYPT_QUERY ioctl is used to query the encryption state.
 */
#घोषणा TAPE390_CRYPT_QUERY _IOR('d', 3, काष्ठा tape390_crypt_info)

/* Values क्रम "kekl1/2_type" and "kekl1/2_type_on_tape" fields */
#घोषणा TAPE390_KEKL_TYPE_NONE 0
#घोषणा TAPE390_KEKL_TYPE_LABEL 1
#घोषणा TAPE390_KEKL_TYPE_HASH 2

काष्ठा tape390_kekl अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर type_on_tape;
	अक्षर label[65];
पूर्ण __attribute__ ((packed));

काष्ठा tape390_kekl_pair अणु
	काष्ठा tape390_kekl kekl[2];
पूर्ण __attribute__ ((packed));

/*
 * The TAPE390_KEKL_SET ioctl is used to set Key Encrypting Key labels.
 */
#घोषणा TAPE390_KEKL_SET _IOW('d', 4, काष्ठा tape390_kekl_pair)

/*
 * The TAPE390_KEKL_QUERY ioctl is used to query Key Encrypting Key labels.
 */
#घोषणा TAPE390_KEKL_QUERY _IOR('d', 5, काष्ठा tape390_kekl_pair)

#पूर्ण_अगर 
