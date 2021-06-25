<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2005, 2012 IBM Corporation
 *
 * Authors:
 *	Kent Yoder <key@linux.vnet.ibm.com>
 *	Seiji Munetoh <munetoh@jp.ibm.com>
 *	Stefan Berger <stefanb@us.ibm.com>
 *	Reiner Sailer <sailer@watson.ibm.com>
 *	Kylene Hall <kjhall@us.ibm.com>
 *	Nayna Jain <nayna@linux.vnet.ibm.com>
 *
 * Access to the event log created by a प्रणाली's firmware / BIOS
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "../tpm.h"
#समावेश "common.h"

अटल पूर्णांक tpm_bios_measurements_खोलो(काष्ठा inode *inode,
					    काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा seq_file *seq;
	काष्ठा tpm_chip_seqops *chip_seqops;
	स्थिर काष्ठा seq_operations *seqops;
	काष्ठा tpm_chip *chip;

	inode_lock(inode);
	अगर (!inode->i_निजी) अणु
		inode_unlock(inode);
		वापस -ENODEV;
	पूर्ण
	chip_seqops = (काष्ठा tpm_chip_seqops *)inode->i_निजी;
	seqops = chip_seqops->seqops;
	chip = chip_seqops->chip;
	get_device(&chip->dev);
	inode_unlock(inode);

	/* now रेजिस्टर seq file */
	err = seq_खोलो(file, seqops);
	अगर (!err) अणु
		seq = file->निजी_data;
		seq->निजी = chip;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tpm_bios_measurements_release(काष्ठा inode *inode,
					 काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = (काष्ठा seq_file *)file->निजी_data;
	काष्ठा tpm_chip *chip = (काष्ठा tpm_chip *)seq->निजी;

	put_device(&chip->dev);

	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations tpm_bios_measurements_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = tpm_bios_measurements_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = tpm_bios_measurements_release,
पूर्ण;

अटल पूर्णांक tpm_पढ़ो_log(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक rc;

	अगर (chip->log.bios_event_log != शून्य) अणु
		dev_dbg(&chip->dev,
			"%s: ERROR - event log already initialized\n",
			__func__);
		वापस -EFAULT;
	पूर्ण

	rc = tpm_पढ़ो_log_acpi(chip);
	अगर (rc != -ENODEV)
		वापस rc;

	rc = tpm_पढ़ो_log_efi(chip);
	अगर (rc != -ENODEV)
		वापस rc;

	वापस tpm_पढ़ो_log_of(chip);
पूर्ण

/*
 * tpm_bios_log_setup() - Read the event log from the firmware
 * @chip: TPM chip to use.
 *
 * If an event log is found then the securityfs files are setup to
 * export it to userspace, otherwise nothing is करोne.
 */
व्योम tpm_bios_log_setup(काष्ठा tpm_chip *chip)
अणु
	स्थिर अक्षर *name = dev_name(&chip->dev);
	अचिन्हित पूर्णांक cnt;
	पूर्णांक log_version;
	पूर्णांक rc = 0;

	अगर (chip->flags & TPM_CHIP_FLAG_VIRTUAL)
		वापस;

	rc = tpm_पढ़ो_log(chip);
	अगर (rc < 0)
		वापस;
	log_version = rc;

	cnt = 0;
	chip->bios_dir[cnt] = securityfs_create_dir(name, शून्य);
	/* NOTE: securityfs_create_dir can वापस ENODEV अगर securityfs is
	 * compiled out. The caller should ignore the ENODEV वापस code.
	 */
	अगर (IS_ERR(chip->bios_dir[cnt]))
		जाओ err;
	cnt++;

	chip->bin_log_seqops.chip = chip;
	अगर (log_version == EFI_TCG2_EVENT_LOG_FORMAT_TCG_2)
		chip->bin_log_seqops.seqops =
			&tpm2_binary_b_measurements_seqops;
	अन्यथा
		chip->bin_log_seqops.seqops =
			&tpm1_binary_b_measurements_seqops;


	chip->bios_dir[cnt] =
	    securityfs_create_file("binary_bios_measurements",
				   0440, chip->bios_dir[0],
				   (व्योम *)&chip->bin_log_seqops,
				   &tpm_bios_measurements_ops);
	अगर (IS_ERR(chip->bios_dir[cnt]))
		जाओ err;
	cnt++;

	अगर (!(chip->flags & TPM_CHIP_FLAG_TPM2)) अणु

		chip->ascii_log_seqops.chip = chip;
		chip->ascii_log_seqops.seqops =
			&tpm1_ascii_b_measurements_seqops;

		chip->bios_dir[cnt] =
			securityfs_create_file("ascii_bios_measurements",
					       0440, chip->bios_dir[0],
					       (व्योम *)&chip->ascii_log_seqops,
					       &tpm_bios_measurements_ops);
		अगर (IS_ERR(chip->bios_dir[cnt]))
			जाओ err;
		cnt++;
	पूर्ण

	वापस;

err:
	chip->bios_dir[cnt] = शून्य;
	tpm_bios_log_tearकरोwn(chip);
	वापस;
पूर्ण

व्योम tpm_bios_log_tearकरोwn(काष्ठा tpm_chip *chip)
अणु
	पूर्णांक i;
	काष्ठा inode *inode;

	/* securityfs_हटाओ currently करोesn't take care of handling sync
	 * between removal and खोलोing of pseuकरो files. To handle this, a
	 * workaround is added by making i_निजी = शून्य here during removal
	 * and to check it during खोलो(), both within inode_lock()/unlock().
	 * This design ensures that खोलो() either safely माला_लो kref or fails.
	 */
	क्रम (i = (TPM_NUM_EVENT_LOG_खाताS - 1); i >= 0; i--) अणु
		अगर (chip->bios_dir[i]) अणु
			inode = d_inode(chip->bios_dir[i]);
			inode_lock(inode);
			inode->i_निजी = शून्य;
			inode_unlock(inode);
			securityfs_हटाओ(chip->bios_dir[i]);
		पूर्ण
	पूर्ण
पूर्ण
