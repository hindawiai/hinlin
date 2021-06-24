<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 James.Bottomley@HansenPartnership.com
 */
#समावेश <linux/slab.h>
#समावेश "tpm-dev.h"

काष्ठा tpmrm_priv अणु
	काष्ठा file_priv priv;
	काष्ठा tpm_space space;
पूर्ण;

अटल पूर्णांक tpmrm_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा tpm_chip *chip;
	काष्ठा tpmrm_priv *priv;
	पूर्णांक rc;

	chip = container_of(inode->i_cdev, काष्ठा tpm_chip, cdevs);
	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	rc = tpm2_init_space(&priv->space, TPM2_SPACE_BUFFER_SIZE);
	अगर (rc) अणु
		kमुक्त(priv);
		वापस -ENOMEM;
	पूर्ण

	tpm_common_खोलो(file, chip, &priv->priv, &priv->space);

	वापस 0;
पूर्ण

अटल पूर्णांक tpmrm_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा file_priv *fpriv = file->निजी_data;
	काष्ठा tpmrm_priv *priv = container_of(fpriv, काष्ठा tpmrm_priv, priv);

	tpm_common_release(file, fpriv);
	tpm2_del_space(fpriv->chip, &priv->space);
	kमुक्त(priv);

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations tpmrm_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.खोलो = tpmrm_खोलो,
	.पढ़ो = tpm_common_पढ़ो,
	.ग_लिखो = tpm_common_ग_लिखो,
	.poll = tpm_common_poll,
	.release = tpmrm_release,
पूर्ण;
