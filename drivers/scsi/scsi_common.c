<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCSI functions used by both the initiator and the target code.
 */

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi_common.h>

/* NB: These are exposed through /proc/scsi/scsi and क्रमm part of the ABI.
 * You may not alter any existing entry (although adding new ones is
 * encouraged once asचिन्हित by ANSI/INCITS T10).
 */
अटल स्थिर अक्षर *स्थिर scsi_device_types[] = अणु
	"Direct-Access    ",
	"Sequential-Access",
	"Printer          ",
	"Processor        ",
	"WORM             ",
	"CD-ROM           ",
	"Scanner          ",
	"Optical Device   ",
	"Medium Changer   ",
	"Communications   ",
	"ASC IT8          ",
	"ASC IT8          ",
	"RAID             ",
	"Enclosure        ",
	"Direct-Access-RBC",
	"Optical card     ",
	"Bridge controller",
	"Object storage   ",
	"Automation/Drive ",
	"Security Manager ",
	"Direct-Access-ZBC",
पूर्ण;

/**
 * scsi_device_type - Return 17-अक्षर string indicating device type.
 * @type: type number to look up
 */
स्थिर अक्षर *scsi_device_type(अचिन्हित type)
अणु
	अगर (type == 0x1e)
		वापस "Well-known LUN   ";
	अगर (type == 0x1f)
		वापस "No Device        ";
	अगर (type >= ARRAY_SIZE(scsi_device_types))
		वापस "Unknown          ";
	वापस scsi_device_types[type];
पूर्ण
EXPORT_SYMBOL(scsi_device_type);

/**
 * scsilun_to_पूर्णांक - convert a scsi_lun to an पूर्णांक
 * @scsilun:	काष्ठा scsi_lun to be converted.
 *
 * Description:
 *     Convert @scsilun from a काष्ठा scsi_lun to a four-byte host byte-ordered
 *     पूर्णांकeger, and वापस the result. The caller must check क्रम
 *     truncation beक्रमe using this function.
 *
 * Notes:
 *     For a description of the LUN क्रमmat, post SCSI-3 see the SCSI
 *     Architecture Model, क्रम SCSI-3 see the SCSI Controller Commands.
 *
 *     Given a काष्ठा scsi_lun of: d2 04 0b 03 00 00 00 00, this function
 *     वापसs the पूर्णांकeger: 0x0b03d204
 *
 *     This encoding will वापस a standard पूर्णांकeger LUN क्रम LUNs smaller
 *     than 256, which typically use a single level LUN काष्ठाure with
 *     addressing method 0.
 */
u64 scsilun_to_पूर्णांक(काष्ठा scsi_lun *scsilun)
अणु
	पूर्णांक i;
	u64 lun;

	lun = 0;
	क्रम (i = 0; i < माप(lun); i += 2)
		lun = lun | (((u64)scsilun->scsi_lun[i] << ((i + 1) * 8)) |
			     ((u64)scsilun->scsi_lun[i + 1] << (i * 8)));
	वापस lun;
पूर्ण
EXPORT_SYMBOL(scsilun_to_पूर्णांक);

/**
 * पूर्णांक_to_scsilun - reverts an पूर्णांक पूर्णांकo a scsi_lun
 * @lun:        पूर्णांकeger to be reverted
 * @scsilun:	काष्ठा scsi_lun to be set.
 *
 * Description:
 *     Reverts the functionality of the scsilun_to_पूर्णांक, which packed
 *     an 8-byte lun value पूर्णांकo an पूर्णांक. This routine unpacks the पूर्णांक
 *     back पूर्णांकo the lun value.
 *
 * Notes:
 *     Given an पूर्णांकeger : 0x0b03d204, this function वापसs a
 *     काष्ठा scsi_lun of: d2 04 0b 03 00 00 00 00
 *
 */
व्योम पूर्णांक_to_scsilun(u64 lun, काष्ठा scsi_lun *scsilun)
अणु
	पूर्णांक i;

	स_रखो(scsilun->scsi_lun, 0, माप(scsilun->scsi_lun));

	क्रम (i = 0; i < माप(lun); i += 2) अणु
		scsilun->scsi_lun[i] = (lun >> 8) & 0xFF;
		scsilun->scsi_lun[i+1] = lun & 0xFF;
		lun = lun >> 16;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(पूर्णांक_to_scsilun);

/**
 * scsi_normalize_sense - normalize मुख्य elements from either fixed or
 *			descriptor sense data क्रमmat पूर्णांकo a common क्रमmat.
 *
 * @sense_buffer:	byte array containing sense data वापसed by device
 * @sb_len:		number of valid bytes in sense_buffer
 * @sshdr:		poपूर्णांकer to instance of काष्ठाure that common
 *			elements are written to.
 *
 * Notes:
 *	The "main elements" from sense data are: response_code, sense_key,
 *	asc, ascq and additional_length (only क्रम descriptor क्रमmat).
 *
 *	Typically this function can be called after a device has
 *	responded to a SCSI command with the CHECK_CONDITION status.
 *
 * Return value:
 *	true अगर valid sense data inक्रमmation found, अन्यथा false;
 */
bool scsi_normalize_sense(स्थिर u8 *sense_buffer, पूर्णांक sb_len,
			  काष्ठा scsi_sense_hdr *sshdr)
अणु
	स_रखो(sshdr, 0, माप(काष्ठा scsi_sense_hdr));

	अगर (!sense_buffer || !sb_len)
		वापस false;

	sshdr->response_code = (sense_buffer[0] & 0x7f);

	अगर (!scsi_sense_valid(sshdr))
		वापस false;

	अगर (sshdr->response_code >= 0x72) अणु
		/*
		 * descriptor क्रमmat
		 */
		अगर (sb_len > 1)
			sshdr->sense_key = (sense_buffer[1] & 0xf);
		अगर (sb_len > 2)
			sshdr->asc = sense_buffer[2];
		अगर (sb_len > 3)
			sshdr->ascq = sense_buffer[3];
		अगर (sb_len > 7)
			sshdr->additional_length = sense_buffer[7];
	पूर्ण अन्यथा अणु
		/*
		 * fixed क्रमmat
		 */
		अगर (sb_len > 2)
			sshdr->sense_key = (sense_buffer[2] & 0xf);
		अगर (sb_len > 7) अणु
			sb_len = (sb_len < (sense_buffer[7] + 8)) ?
					 sb_len : (sense_buffer[7] + 8);
			अगर (sb_len > 12)
				sshdr->asc = sense_buffer[12];
			अगर (sb_len > 13)
				sshdr->ascq = sense_buffer[13];
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(scsi_normalize_sense);

/**
 * scsi_sense_desc_find - search क्रम a given descriptor type in	descriptor sense data क्रमmat.
 * @sense_buffer:	byte array of descriptor क्रमmat sense data
 * @sb_len:		number of valid bytes in sense_buffer
 * @desc_type:		value of descriptor type to find
 *			(e.g. 0 -> inक्रमmation)
 *
 * Notes:
 *	only valid when sense data is in descriptor क्रमmat
 *
 * Return value:
 *	poपूर्णांकer to start of (first) descriptor अगर found अन्यथा शून्य
 */
स्थिर u8 * scsi_sense_desc_find(स्थिर u8 * sense_buffer, पूर्णांक sb_len,
				पूर्णांक desc_type)
अणु
	पूर्णांक add_sen_len, add_len, desc_len, k;
	स्थिर u8 * descp;

	अगर ((sb_len < 8) || (0 == (add_sen_len = sense_buffer[7])))
		वापस शून्य;
	अगर ((sense_buffer[0] < 0x72) || (sense_buffer[0] > 0x73))
		वापस शून्य;
	add_sen_len = (add_sen_len < (sb_len - 8)) ?
			add_sen_len : (sb_len - 8);
	descp = &sense_buffer[8];
	क्रम (desc_len = 0, k = 0; k < add_sen_len; k += desc_len) अणु
		descp += desc_len;
		add_len = (k < (add_sen_len - 1)) ? descp[1]: -1;
		desc_len = add_len + 2;
		अगर (descp[0] == desc_type)
			वापस descp;
		अगर (add_len < 0) // लघु descriptor ??
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(scsi_sense_desc_find);

/**
 * scsi_build_sense_buffer - build sense data in a buffer
 * @desc:	Sense क्रमmat (non-zero == descriptor क्रमmat,
 *              0 == fixed क्रमmat)
 * @buf:	Where to build sense data
 * @key:	Sense key
 * @asc:	Additional sense code
 * @ascq:	Additional sense code qualअगरier
 *
 **/
व्योम scsi_build_sense_buffer(पूर्णांक desc, u8 *buf, u8 key, u8 asc, u8 ascq)
अणु
	अगर (desc) अणु
		buf[0] = 0x72;	/* descriptor, current */
		buf[1] = key;
		buf[2] = asc;
		buf[3] = ascq;
		buf[7] = 0;
	पूर्ण अन्यथा अणु
		buf[0] = 0x70;	/* fixed, current */
		buf[2] = key;
		buf[7] = 0xa;
		buf[12] = asc;
		buf[13] = ascq;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(scsi_build_sense_buffer);

/**
 * scsi_set_sense_inक्रमmation - set the inक्रमmation field in a
 *		क्रमmatted sense data buffer
 * @buf:	Where to build sense data
 * @buf_len:    buffer length
 * @info:	64-bit inक्रमmation value to be set
 *
 * Return value:
 *	0 on success or -EINVAL क्रम invalid sense buffer length
 **/
पूर्णांक scsi_set_sense_inक्रमmation(u8 *buf, पूर्णांक buf_len, u64 info)
अणु
	अगर ((buf[0] & 0x7f) == 0x72) अणु
		u8 *ucp, len;

		len = buf[7];
		ucp = (अक्षर *)scsi_sense_desc_find(buf, len + 8, 0);
		अगर (!ucp) अणु
			buf[7] = len + 0xc;
			ucp = buf + 8 + len;
		पूर्ण

		अगर (buf_len < len + 0xc)
			/* Not enough room क्रम info */
			वापस -EINVAL;

		ucp[0] = 0;
		ucp[1] = 0xa;
		ucp[2] = 0x80; /* Valid bit */
		ucp[3] = 0;
		put_unaligned_be64(info, &ucp[4]);
	पूर्ण अन्यथा अगर ((buf[0] & 0x7f) == 0x70) अणु
		/*
		 * Only set the 'VALID' bit अगर we can represent the value
		 * correctly; otherwise just fill out the lower bytes and
		 * clear the 'VALID' flag.
		 */
		अगर (info <= 0xffffffffUL)
			buf[0] |= 0x80;
		अन्यथा
			buf[0] &= 0x7f;
		put_unaligned_be32((u32)info, &buf[3]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_set_sense_inक्रमmation);

/**
 * scsi_set_sense_field_poपूर्णांकer - set the field poपूर्णांकer sense key
 *		specअगरic inक्रमmation in a क्रमmatted sense data buffer
 * @buf:	Where to build sense data
 * @buf_len:    buffer length
 * @fp:		field poपूर्णांकer to be set
 * @bp:		bit poपूर्णांकer to be set
 * @cd:		command/data bit
 *
 * Return value:
 *	0 on success or -EINVAL क्रम invalid sense buffer length
 */
पूर्णांक scsi_set_sense_field_poपूर्णांकer(u8 *buf, पूर्णांक buf_len, u16 fp, u8 bp, bool cd)
अणु
	u8 *ucp, len;

	अगर ((buf[0] & 0x7f) == 0x72) अणु
		len = buf[7];
		ucp = (अक्षर *)scsi_sense_desc_find(buf, len + 8, 2);
		अगर (!ucp) अणु
			buf[7] = len + 8;
			ucp = buf + 8 + len;
		पूर्ण

		अगर (buf_len < len + 8)
			/* Not enough room क्रम info */
			वापस -EINVAL;

		ucp[0] = 2;
		ucp[1] = 6;
		ucp[4] = 0x80; /* Valid bit */
		अगर (cd)
			ucp[4] |= 0x40;
		अगर (bp < 0x8)
			ucp[4] |= 0x8 | bp;
		put_unaligned_be16(fp, &ucp[5]);
	पूर्ण अन्यथा अगर ((buf[0] & 0x7f) == 0x70) अणु
		len = buf[7];
		अगर (len < 18)
			buf[7] = 18;

		buf[15] = 0x80;
		अगर (cd)
			buf[15] |= 0x40;
		अगर (bp < 0x8)
			buf[15] |= 0x8 | bp;
		put_unaligned_be16(fp, &buf[16]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_set_sense_field_poपूर्णांकer);
