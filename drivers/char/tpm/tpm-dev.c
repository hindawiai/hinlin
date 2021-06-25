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
 * Device file प्रणाली पूर्णांकerface to the TPM
 */
#समावेश <linux/slab.h>
#समावेश "tpm-dev.h"

अटल पूर्णांक tpm_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा tpm_chip *chip;
	काष्ठा file_priv *priv;

	chip = container_of(inode->i_cdev, काष्ठा tpm_chip, cdev);

	/* It's assured that the chip will be खोलोed just once,
	 * by the check of is_खोलो variable, which is रक्षित
	 * by driver_lock. */
	अगर (test_and_set_bit(0, &chip->is_खोलो)) अणु
		dev_dbg(&chip->dev, "Another process owns this TPM\n");
		वापस -EBUSY;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		जाओ out;

	tpm_common_खोलो(file, chip, priv, शून्य);

	वापस 0;

 out:
	clear_bit(0, &chip->is_खोलो);
	वापस -ENOMEM;
पूर्ण

/*
 * Called on file बंद
 */
अटल पूर्णांक tpm_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा file_priv *priv = file->निजी_data;

	tpm_common_release(file, priv);
	clear_bit(0, &priv->chip->is_खोलो);
	kमुक्त(priv);

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations tpm_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.खोलो = tpm_खोलो,
	.पढ़ो = tpm_common_पढ़ो,
	.ग_लिखो = tpm_common_ग_लिखो,
	.poll = tpm_common_poll,
	.release = tpm_release,
पूर्ण;
