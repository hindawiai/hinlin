<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 IBM Corporation
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Copyright (C) 2013 Obsidian Research Corp
 * Jason Gunthorpe <jgunthorpe@obsidianresearch.com>
 *
 * sysfs fileप्रणाली inspection पूर्णांकerface to the TPM
 */
#समावेश <linux/device.h>
#समावेश "tpm.h"

काष्ठा tpm_पढ़ोpubek_out अणु
	u8 algorithm[4];
	u8 encscheme[2];
	u8 sigscheme[2];
	__be32 paramsize;
	u8 parameters[12];
	__be32 keysize;
	u8 modulus[256];
	u8 checksum[20];
पूर्ण __packed;

#घोषणा READ_PUBEK_RESULT_MIN_BODY_SIZE (28 + 256)
#घोषणा TPM_ORD_READPUBEK 124

अटल sमाप_प्रकार pubek_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा tpm_buf tpm_buf;
	काष्ठा tpm_पढ़ोpubek_out *out;
	पूर्णांक i;
	अक्षर *str = buf;
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	अक्षर anti_replay[20];

	स_रखो(&anti_replay, 0, माप(anti_replay));

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm_buf_init(&tpm_buf, TPM_TAG_RQU_COMMAND, TPM_ORD_READPUBEK))
		जाओ out_ops;

	tpm_buf_append(&tpm_buf, anti_replay, माप(anti_replay));

	अगर (tpm_transmit_cmd(chip, &tpm_buf, READ_PUBEK_RESULT_MIN_BODY_SIZE,
			     "attempting to read the PUBEK"))
		जाओ out_buf;

	out = (काष्ठा tpm_पढ़ोpubek_out *)&tpm_buf.data[10];
	str +=
	    प्र_लिखो(str,
		    "Algorithm: %4ph\n"
		    "Encscheme: %2ph\n"
		    "Sigscheme: %2ph\n"
		    "Parameters: %12ph\n"
		    "Modulus length: %d\n"
		    "Modulus:\n",
		    out->algorithm,
		    out->encscheme,
		    out->sigscheme,
		    out->parameters,
		    be32_to_cpu(out->keysize));

	क्रम (i = 0; i < 256; i += 16)
		str += प्र_लिखो(str, "%16ph\n", &out->modulus[i]);

out_buf:
	tpm_buf_destroy(&tpm_buf);
out_ops:
	tpm_put_ops(chip);
	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR_RO(pubek);

अटल sमाप_प्रकार pcrs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	cap_t cap;
	u8 digest[TPM_DIGEST_SIZE];
	u32 i, j, num_pcrs;
	अक्षर *str = buf;
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm1_अ_लोap(chip, TPM_CAP_PROP_PCR, &cap,
			"attempting to determine the number of PCRS",
			माप(cap.num_pcrs))) अणु
		tpm_put_ops(chip);
		वापस 0;
	पूर्ण

	num_pcrs = be32_to_cpu(cap.num_pcrs);
	क्रम (i = 0; i < num_pcrs; i++) अणु
		अगर (tpm1_pcr_पढ़ो(chip, i, digest)) अणु
			str = buf;
			अवरोध;
		पूर्ण
		str += प्र_लिखो(str, "PCR-%02d: ", i);
		क्रम (j = 0; j < TPM_DIGEST_SIZE; j++)
			str += प्र_लिखो(str, "%02X ", digest[j]);
		str += प्र_लिखो(str, "\n");
	पूर्ण
	tpm_put_ops(chip);
	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR_RO(pcrs);

अटल sमाप_प्रकार enabled_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	sमाप_प्रकार rc = 0;
	cap_t cap;

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm1_अ_लोap(chip, TPM_CAP_FLAG_PERM, &cap,
			"attempting to determine the permanent enabled state",
			माप(cap.perm_flags)))
		जाओ out_ops;

	rc = प्र_लिखो(buf, "%d\n", !cap.perm_flags.disable);
out_ops:
	tpm_put_ops(chip);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(enabled);

अटल sमाप_प्रकार active_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	sमाप_प्रकार rc = 0;
	cap_t cap;

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm1_अ_लोap(chip, TPM_CAP_FLAG_PERM, &cap,
			"attempting to determine the permanent active state",
			माप(cap.perm_flags)))
		जाओ out_ops;

	rc = प्र_लिखो(buf, "%d\n", !cap.perm_flags.deactivated);
out_ops:
	tpm_put_ops(chip);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(active);

अटल sमाप_प्रकार owned_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	sमाप_प्रकार rc = 0;
	cap_t cap;

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm1_अ_लोap(to_tpm_chip(dev), TPM_CAP_PROP_OWNER, &cap,
			"attempting to determine the owner state",
			माप(cap.owned)))
		जाओ out_ops;

	rc = प्र_लिखो(buf, "%d\n", cap.owned);
out_ops:
	tpm_put_ops(chip);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(owned);

अटल sमाप_प्रकार temp_deactivated_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	sमाप_प्रकार rc = 0;
	cap_t cap;

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm1_अ_लोap(to_tpm_chip(dev), TPM_CAP_FLAG_VOL, &cap,
			"attempting to determine the temporary state",
			माप(cap.stclear_flags)))
		जाओ out_ops;

	rc = प्र_लिखो(buf, "%d\n", cap.stclear_flags.deactivated);
out_ops:
	tpm_put_ops(chip);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(temp_deactivated);

अटल sमाप_प्रकार caps_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	काष्ठा tpm1_version *version;
	sमाप_प्रकार rc = 0;
	अक्षर *str = buf;
	cap_t cap;

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	अगर (tpm1_अ_लोap(chip, TPM_CAP_PROP_MANUFACTURER, &cap,
			"attempting to determine the manufacturer",
			माप(cap.manufacturer_id)))
		जाओ out_ops;

	str += प्र_लिखो(str, "Manufacturer: 0x%x\n",
		       be32_to_cpu(cap.manufacturer_id));

	/* TPM 1.2 */
	अगर (!tpm1_अ_लोap(chip, TPM_CAP_VERSION_1_2, &cap,
			 "attempting to determine the 1.2 version",
			 माप(cap.version2))) अणु
		version = &cap.version2.version;
		जाओ out_prपूर्णांक;
	पूर्ण

	/* TPM 1.1 */
	अगर (tpm1_अ_लोap(chip, TPM_CAP_VERSION_1_1, &cap,
			"attempting to determine the 1.1 version",
			माप(cap.version1))) अणु
		जाओ out_ops;
	पूर्ण

	version = &cap.version1;

out_prपूर्णांक:
	str += प्र_लिखो(str,
		       "TCG version: %d.%d\nFirmware version: %d.%d\n",
		       version->major, version->minor,
		       version->rev_major, version->rev_minor);

	rc = str - buf;

out_ops:
	tpm_put_ops(chip);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(caps);

अटल sमाप_प्रकार cancel_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	अगर (tpm_try_get_ops(chip))
		वापस 0;

	chip->ops->cancel(chip);
	tpm_put_ops(chip);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(cancel);

अटल sमाप_प्रकार durations_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	अगर (chip->duration[TPM_LONG] == 0)
		वापस 0;

	वापस प्र_लिखो(buf, "%d %d %d [%s]\n",
		       jअगरfies_to_usecs(chip->duration[TPM_SHORT]),
		       jअगरfies_to_usecs(chip->duration[TPM_MEDIUM]),
		       jअगरfies_to_usecs(chip->duration[TPM_LONG]),
		       chip->duration_adjusted
		       ? "adjusted" : "original");
पूर्ण
अटल DEVICE_ATTR_RO(durations);

अटल sमाप_प्रकार समयouts_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	वापस प्र_लिखो(buf, "%d %d %d %d [%s]\n",
		       jअगरfies_to_usecs(chip->समयout_a),
		       jअगरfies_to_usecs(chip->समयout_b),
		       jअगरfies_to_usecs(chip->समयout_c),
		       jअगरfies_to_usecs(chip->समयout_d),
		       chip->समयout_adjusted
		       ? "adjusted" : "original");
पूर्ण
अटल DEVICE_ATTR_RO(समयouts);

अटल sमाप_प्रकार tpm_version_major_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	वापस प्र_लिखो(buf, "%s\n", chip->flags & TPM_CHIP_FLAG_TPM2
		       ? "2" : "1");
पूर्ण
अटल DEVICE_ATTR_RO(tpm_version_major);

अटल काष्ठा attribute *tpm1_dev_attrs[] = अणु
	&dev_attr_pubek.attr,
	&dev_attr_pcrs.attr,
	&dev_attr_enabled.attr,
	&dev_attr_active.attr,
	&dev_attr_owned.attr,
	&dev_attr_temp_deactivated.attr,
	&dev_attr_caps.attr,
	&dev_attr_cancel.attr,
	&dev_attr_durations.attr,
	&dev_attr_समयouts.attr,
	&dev_attr_tpm_version_major.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *tpm2_dev_attrs[] = अणु
	&dev_attr_tpm_version_major.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tpm1_dev_group = अणु
	.attrs = tpm1_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group tpm2_dev_group = अणु
	.attrs = tpm2_dev_attrs,
पूर्ण;

काष्ठा tpm_pcr_attr अणु
	पूर्णांक alg_id;
	पूर्णांक pcr;
	काष्ठा device_attribute attr;
पूर्ण;

#घोषणा to_tpm_pcr_attr(a) container_of(a, काष्ठा tpm_pcr_attr, attr)

अटल sमाप_प्रकार pcr_value_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tpm_pcr_attr *ha = to_tpm_pcr_attr(attr);
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	काष्ठा tpm_digest digest;
	पूर्णांक i;
	पूर्णांक digest_size = 0;
	पूर्णांक rc;
	अक्षर *str = buf;

	क्रम (i = 0; i < chip->nr_allocated_banks; i++)
		अगर (ha->alg_id == chip->allocated_banks[i].alg_id)
			digest_size = chip->allocated_banks[i].digest_size;
	/* should never happen */
	अगर (!digest_size)
		वापस -EINVAL;

	digest.alg_id = ha->alg_id;
	rc = tpm_pcr_पढ़ो(chip, ha->pcr, &digest);
	अगर (rc)
		वापस rc;
	क्रम (i = 0; i < digest_size; i++)
		str += प्र_लिखो(str, "%02X", digest.digest[i]);
	str += प्र_लिखो(str, "\n");

	वापस str - buf;
पूर्ण

/*
 * The following set of defines represents all the magic to build
 * the per hash attribute groups क्रम displaying each bank of PCRs.
 * The only slight problem with this approach is that every PCR is
 * hard coded to be present, so you करोn't know अगर an PCR is missing
 * until a cat of the file वापसs -EINVAL
 *
 * Also note you must ignore checkpatch warnings in this macro
 * code. This is deep macro magic that checkpatch.pl करोesn't
 * understand.
 */

/* Note, this must match TPM2_PLATFORM_PCR which is fixed at 24. */
#घोषणा _TPM_HELPER(_alg, _hash, F) \
	F(_alg, _hash, 0)	    \
	F(_alg, _hash, 1)	    \
	F(_alg, _hash, 2)	    \
	F(_alg, _hash, 3)	    \
	F(_alg, _hash, 4)	    \
	F(_alg, _hash, 5)	    \
	F(_alg, _hash, 6)	    \
	F(_alg, _hash, 7)	    \
	F(_alg, _hash, 8)	    \
	F(_alg, _hash, 9)	    \
	F(_alg, _hash, 10)	    \
	F(_alg, _hash, 11)	    \
	F(_alg, _hash, 12)	    \
	F(_alg, _hash, 13)	    \
	F(_alg, _hash, 14)	    \
	F(_alg, _hash, 15)	    \
	F(_alg, _hash, 16)	    \
	F(_alg, _hash, 17)	    \
	F(_alg, _hash, 18)	    \
	F(_alg, _hash, 19)	    \
	F(_alg, _hash, 20)	    \
	F(_alg, _hash, 21)	    \
	F(_alg, _hash, 22)	    \
	F(_alg, _hash, 23)

/* ignore checkpatch warning about trailing ; in macro. */
#घोषणा PCR_ATTR(_alg, _hash, _pcr)				   \
	अटल काष्ठा tpm_pcr_attr dev_attr_pcr_##_hash##_##_pcr = अणु	\
		.alg_id = _alg,					   \
		.pcr = _pcr,					   \
		.attr = अणु					   \
			.attr = अणु				   \
				.name = __stringअगरy(_pcr),	   \
				.mode = 0444			   \
			पूर्ण,					   \
			.show = pcr_value_show			   \
		पूर्ण						   \
	पूर्ण;

#घोषणा PCR_ATTRS(_alg, _hash)			\
	_TPM_HELPER(_alg, _hash, PCR_ATTR)

/* ignore checkpatch warning about trailing , in macro. */
#घोषणा PCR_ATTR_VAL(_alg, _hash, _pcr)		\
	&dev_attr_pcr_##_hash##_##_pcr.attr.attr,

#घोषणा PCR_ATTR_GROUP_ARRAY(_alg, _hash)		       \
	अटल काष्ठा attribute *pcr_group_attrs_##_hash[] = अणु \
		_TPM_HELPER(_alg, _hash, PCR_ATTR_VAL)	       \
		शून्य					       \
	पूर्ण

#घोषणा PCR_ATTR_GROUP(_alg, _hash)			    \
	अटल काष्ठा attribute_group pcr_group_##_hash = अणु \
		.name = "pcr-" __stringअगरy(_hash),	    \
		.attrs = pcr_group_attrs_##_hash	    \
	पूर्ण

#घोषणा PCR_ATTR_BUILD(_alg, _hash)	   \
	PCR_ATTRS(_alg, _hash)		   \
	PCR_ATTR_GROUP_ARRAY(_alg, _hash); \
	PCR_ATTR_GROUP(_alg, _hash)
/*
 * End of macro काष्ठाure to build an attribute group containing 24
 * PCR value files क्रम each supported hash algorithm
 */

/*
 * The next set of macros implements the cleverness क्रम each hash to
 * build a अटल attribute group called pcr_group_<hash> which can be
 * added to chip->groups[].
 *
 * The first argument is the TPM algorithm id and the second is the
 * hash used as both the suffix and the group name.  Note: the group
 * name is a directory in the top level tpm class with the name
 * pcr-<hash>, so it must not clash with any other names alपढ़ोy
 * in the sysfs directory.
 */
PCR_ATTR_BUILD(TPM_ALG_SHA1, sha1);
PCR_ATTR_BUILD(TPM_ALG_SHA256, sha256);
PCR_ATTR_BUILD(TPM_ALG_SHA384, sha384);
PCR_ATTR_BUILD(TPM_ALG_SHA512, sha512);
PCR_ATTR_BUILD(TPM_ALG_SM3_256, sm3);


व्योम tpm_sysfs_add_device(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक i;

	WARN_ON(chip->groups_cnt != 0);

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2)
		chip->groups[chip->groups_cnt++] = &tpm2_dev_group;
	अन्यथा
		chip->groups[chip->groups_cnt++] = &tpm1_dev_group;

	/* add one group क्रम each bank hash */
	क्रम (i = 0; i < chip->nr_allocated_banks; i++) अणु
		चयन (chip->allocated_banks[i].alg_id) अणु
		हाल TPM_ALG_SHA1:
			chip->groups[chip->groups_cnt++] = &pcr_group_sha1;
			अवरोध;
		हाल TPM_ALG_SHA256:
			chip->groups[chip->groups_cnt++] = &pcr_group_sha256;
			अवरोध;
		हाल TPM_ALG_SHA384:
			chip->groups[chip->groups_cnt++] = &pcr_group_sha384;
			अवरोध;
		हाल TPM_ALG_SHA512:
			chip->groups[chip->groups_cnt++] = &pcr_group_sha512;
			अवरोध;
		हाल TPM_ALG_SM3_256:
			chip->groups[chip->groups_cnt++] = &pcr_group_sm3;
			अवरोध;
		शेष:
			/*
			 * If triggers, send a patch to add both a
			 * PCR_ATTR_BUILD() macro above क्रम the
			 * missing algorithm as well as an additional
			 * हाल in this चयन statement.
			 */
			dev_err(&chip->dev,
				"TPM with unsupported bank algorithm 0x%04x",
				chip->allocated_banks[i].alg_id);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * This will only trigger अगर someone has added an additional
	 * hash to the tpm_algorithms क्रमागत without incrementing
	 * TPM_MAX_HASHES.
	 */
	WARN_ON(chip->groups_cnt > TPM_MAX_HASHES + 1);
पूर्ण
