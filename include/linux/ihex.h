<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Compact binary representation of ihex records. Some devices need their
 * firmware loaded in strange orders rather than a single big blob, but
 * actually parsing ihex-as-text within the kernel seems silly. Thus,...
 */

#अगर_अघोषित __LINUX_IHEX_H__
#घोषणा __LINUX_IHEX_H__

#समावेश <linux/types.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>

/* Intel HEX files actually limit the length to 256 bytes, but we have
   drivers which would benefit from using separate records which are
   दीर्घer than that, so we extend to 16 bits of length */
काष्ठा ihex_binrec अणु
	__be32 addr;
	__be16 len;
	uपूर्णांक8_t data[];
पूर्ण __attribute__((packed));

अटल अंतरभूत uपूर्णांक16_t ihex_binrec_size(स्थिर काष्ठा ihex_binrec *p)
अणु
	वापस be16_to_cpu(p->len) + माप(*p);
पूर्ण

/* Find the next record, taking पूर्णांकo account the 4-byte alignment */
अटल अंतरभूत स्थिर काष्ठा ihex_binrec *
__ihex_next_binrec(स्थिर काष्ठा ihex_binrec *rec)
अणु
	स्थिर व्योम *p = rec;

	वापस p + ALIGN(ihex_binrec_size(rec), 4);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ihex_binrec *
ihex_next_binrec(स्थिर काष्ठा ihex_binrec *rec)
अणु
	rec = __ihex_next_binrec(rec);

	वापस be16_to_cpu(rec->len) ? rec : शून्य;
पूर्ण

/* Check that ihex_next_binrec() won't take us off the end of the image... */
अटल अंतरभूत पूर्णांक ihex_validate_fw(स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा ihex_binrec *end, *rec;

	rec = (स्थिर व्योम *)fw->data;
	end = (स्थिर व्योम *)&fw->data[fw->size - माप(*end)];

	क्रम (; rec <= end; rec = __ihex_next_binrec(rec)) अणु
		/* Zero length marks end of records */
		अगर (rec == end && !be16_to_cpu(rec->len))
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Request firmware and validate it so that we can trust we won't
 * run off the end जबतक पढ़ोing records... */
अटल अंतरभूत पूर्णांक request_ihex_firmware(स्थिर काष्ठा firmware **fw,
					स्थिर अक्षर *fw_name,
					काष्ठा device *dev)
अणु
	स्थिर काष्ठा firmware *lfw;
	पूर्णांक ret;

	ret = request_firmware(&lfw, fw_name, dev);
	अगर (ret)
		वापस ret;
	ret = ihex_validate_fw(lfw);
	अगर (ret) अणु
		dev_err(dev, "Firmware \"%s\" not valid IHEX records\n",
			fw_name);
		release_firmware(lfw);
		वापस ret;
	पूर्ण
	*fw = lfw;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* __LINUX_IHEX_H__ */
