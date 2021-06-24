<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip / Aपंचांगel ECC (I2C) driver.
 *
 * Copyright (c) 2017, Microchip Technology Inc.
 * Author: Tuकरोr Ambarus <tuकरोr.ambarus@microchip.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/ecdh.h>
#समावेश <crypto/kpp.h>
#समावेश "atmel-i2c.h"

अटल काष्ठा aपंचांगel_ecc_driver_data driver_data;

/**
 * काष्ठा aपंचांगel_ecdh_ctx - transक्रमmation context
 * @client     : poपूर्णांकer to i2c client device
 * @fallback   : used क्रम unsupported curves or when user wants to use its own
 *               निजी key.
 * @खुला_key : generated when calling set_secret(). It's the responsibility
 *               of the user to not call set_secret() जबतक
 *               generate_खुला_key() or compute_shared_secret() are in flight.
 * @curve_id   : elliptic curve id
 * @करो_fallback: true when the device करोesn't support the curve or when the user
 *               wants to use its own निजी key.
 */
काष्ठा aपंचांगel_ecdh_ctx अणु
	काष्ठा i2c_client *client;
	काष्ठा crypto_kpp *fallback;
	स्थिर u8 *खुला_key;
	अचिन्हित पूर्णांक curve_id;
	bool करो_fallback;
पूर्ण;

अटल व्योम aपंचांगel_ecdh_करोne(काष्ठा aपंचांगel_i2c_work_data *work_data, व्योम *areq,
			    पूर्णांक status)
अणु
	काष्ठा kpp_request *req = areq;
	काष्ठा aपंचांगel_i2c_cmd *cmd = &work_data->cmd;
	माप_प्रकार copied, n_sz;

	अगर (status)
		जाओ मुक्त_work_data;

	/* might want less than we've got */
	n_sz = min_t(माप_प्रकार, ATMEL_ECC_NIST_P256_N_SIZE, req->dst_len);

	/* copy the shared secret */
	copied = sg_copy_from_buffer(req->dst, sg_nents_क्रम_len(req->dst, n_sz),
				     &cmd->data[RSP_DATA_IDX], n_sz);
	अगर (copied != n_sz)
		status = -EINVAL;

	/* fall through */
मुक्त_work_data:
	kमुक्त_sensitive(work_data);
	kpp_request_complete(req, status);
पूर्ण

/*
 * A अक्रमom निजी key is generated and stored in the device. The device
 * वापसs the pair खुला key.
 */
अटल पूर्णांक aपंचांगel_ecdh_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा aपंचांगel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा aपंचांगel_i2c_cmd *cmd;
	व्योम *खुला_key;
	काष्ठा ecdh params;
	पूर्णांक ret = -ENOMEM;

	/* मुक्त the old खुला key, अगर any */
	kमुक्त(ctx->खुला_key);
	/* make sure you करोn't मुक्त the old खुला key twice */
	ctx->खुला_key = शून्य;

	अगर (crypto_ecdh_decode_key(buf, len, &params) < 0) अणु
		dev_err(&ctx->client->dev, "crypto_ecdh_decode_key failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (params.key_size) अणु
		/* fallback to ecdh software implementation */
		ctx->करो_fallback = true;
		वापस crypto_kpp_set_secret(ctx->fallback, buf, len);
	पूर्ण

	cmd = kदो_स्मृति(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	/*
	 * The device only supports NIST P256 ECC keys. The खुला key size will
	 * always be the same. Use a macro क्रम the key size to aव्योम unnecessary
	 * computations.
	 */
	खुला_key = kदो_स्मृति(ATMEL_ECC_PUBKEY_SIZE, GFP_KERNEL);
	अगर (!खुला_key)
		जाओ मुक्त_cmd;

	ctx->करो_fallback = false;

	aपंचांगel_i2c_init_genkey_cmd(cmd, DATA_SLOT_2);

	ret = aपंचांगel_i2c_send_receive(ctx->client, cmd);
	अगर (ret)
		जाओ मुक्त_खुला_key;

	/* save the खुला key */
	स_नकल(खुला_key, &cmd->data[RSP_DATA_IDX], ATMEL_ECC_PUBKEY_SIZE);
	ctx->खुला_key = खुला_key;

	kमुक्त(cmd);
	वापस 0;

मुक्त_खुला_key:
	kमुक्त(खुला_key);
मुक्त_cmd:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_ecdh_generate_खुला_key(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा aपंचांगel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	माप_प्रकार copied, nbytes;
	पूर्णांक ret = 0;

	अगर (ctx->करो_fallback) अणु
		kpp_request_set_tfm(req, ctx->fallback);
		वापस crypto_kpp_generate_खुला_key(req);
	पूर्ण

	अगर (!ctx->खुला_key)
		वापस -EINVAL;

	/* might want less than we've got */
	nbytes = min_t(माप_प्रकार, ATMEL_ECC_PUBKEY_SIZE, req->dst_len);

	/* खुला key was saved at निजी key generation */
	copied = sg_copy_from_buffer(req->dst,
				     sg_nents_क्रम_len(req->dst, nbytes),
				     ctx->खुला_key, nbytes);
	अगर (copied != nbytes)
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_ecdh_compute_shared_secret(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा aपंचांगel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा aपंचांगel_i2c_work_data *work_data;
	gfp_t gfp;
	पूर्णांक ret;

	अगर (ctx->करो_fallback) अणु
		kpp_request_set_tfm(req, ctx->fallback);
		वापस crypto_kpp_compute_shared_secret(req);
	पूर्ण

	/* must have exactly two poपूर्णांकs to be on the curve */
	अगर (req->src_len != ATMEL_ECC_PUBKEY_SIZE)
		वापस -EINVAL;

	gfp = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ? GFP_KERNEL :
							     GFP_ATOMIC;

	work_data = kदो_स्मृति(माप(*work_data), gfp);
	अगर (!work_data)
		वापस -ENOMEM;

	work_data->ctx = ctx;
	work_data->client = ctx->client;

	ret = aपंचांगel_i2c_init_ecdh_cmd(&work_data->cmd, req->src);
	अगर (ret)
		जाओ मुक्त_work_data;

	aपंचांगel_i2c_enqueue(work_data, aपंचांगel_ecdh_करोne, req);

	वापस -EINPROGRESS;

मुक्त_work_data:
	kमुक्त(work_data);
	वापस ret;
पूर्ण

अटल काष्ठा i2c_client *aपंचांगel_ecc_i2c_client_alloc(व्योम)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv, *min_i2c_priv = शून्य;
	काष्ठा i2c_client *client = ERR_PTR(-ENODEV);
	पूर्णांक min_tfm_cnt = पूर्णांक_उच्च;
	पूर्णांक tfm_cnt;

	spin_lock(&driver_data.i2c_list_lock);

	अगर (list_empty(&driver_data.i2c_client_list)) अणु
		spin_unlock(&driver_data.i2c_list_lock);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	list_क्रम_each_entry(i2c_priv, &driver_data.i2c_client_list,
			    i2c_client_list_node) अणु
		tfm_cnt = atomic_पढ़ो(&i2c_priv->tfm_count);
		अगर (tfm_cnt < min_tfm_cnt) अणु
			min_tfm_cnt = tfm_cnt;
			min_i2c_priv = i2c_priv;
		पूर्ण
		अगर (!min_tfm_cnt)
			अवरोध;
	पूर्ण

	अगर (min_i2c_priv) अणु
		atomic_inc(&min_i2c_priv->tfm_count);
		client = min_i2c_priv->client;
	पूर्ण

	spin_unlock(&driver_data.i2c_list_lock);

	वापस client;
पूर्ण

अटल व्योम aपंचांगel_ecc_i2c_client_मुक्त(काष्ठा i2c_client *client)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);

	atomic_dec(&i2c_priv->tfm_count);
पूर्ण

अटल पूर्णांक aपंचांगel_ecdh_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	स्थिर अक्षर *alg = kpp_alg_name(tfm);
	काष्ठा crypto_kpp *fallback;
	काष्ठा aपंचांगel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->curve_id = ECC_CURVE_NIST_P256;
	ctx->client = aपंचांगel_ecc_i2c_client_alloc();
	अगर (IS_ERR(ctx->client)) अणु
		pr_err("tfm - i2c_client binding failed\n");
		वापस PTR_ERR(ctx->client);
	पूर्ण

	fallback = crypto_alloc_kpp(alg, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(fallback)) अणु
		dev_err(&ctx->client->dev, "Failed to allocate transformation for '%s': %ld\n",
			alg, PTR_ERR(fallback));
		वापस PTR_ERR(fallback);
	पूर्ण

	crypto_kpp_set_flags(fallback, crypto_kpp_get_flags(tfm));
	ctx->fallback = fallback;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_ecdh_निकास_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा aपंचांगel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	kमुक्त(ctx->खुला_key);
	crypto_मुक्त_kpp(ctx->fallback);
	aपंचांगel_ecc_i2c_client_मुक्त(ctx->client);
पूर्ण

अटल अचिन्हित पूर्णांक aपंचांगel_ecdh_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा aपंचांगel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	अगर (ctx->fallback)
		वापस crypto_kpp_maxsize(ctx->fallback);

	/*
	 * The device only supports NIST P256 ECC keys. The खुला key size will
	 * always be the same. Use a macro क्रम the key size to aव्योम unnecessary
	 * computations.
	 */
	वापस ATMEL_ECC_PUBKEY_SIZE;
पूर्ण

अटल काष्ठा kpp_alg aपंचांगel_ecdh_nist_p256 = अणु
	.set_secret = aपंचांगel_ecdh_set_secret,
	.generate_खुला_key = aपंचांगel_ecdh_generate_खुला_key,
	.compute_shared_secret = aपंचांगel_ecdh_compute_shared_secret,
	.init = aपंचांगel_ecdh_init_tfm,
	.निकास = aपंचांगel_ecdh_निकास_tfm,
	.max_size = aपंचांगel_ecdh_max_size,
	.base = अणु
		.cra_flags = CRYPTO_ALG_NEED_FALLBACK,
		.cra_name = "ecdh-nist-p256",
		.cra_driver_name = "atmel-ecdh",
		.cra_priority = ATMEL_ECC_PRIORITY,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा aपंचांगel_ecdh_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक aपंचांगel_ecc_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv;
	पूर्णांक ret;

	ret = aपंचांगel_i2c_probe(client, id);
	अगर (ret)
		वापस ret;

	i2c_priv = i2c_get_clientdata(client);

	spin_lock(&driver_data.i2c_list_lock);
	list_add_tail(&i2c_priv->i2c_client_list_node,
		      &driver_data.i2c_client_list);
	spin_unlock(&driver_data.i2c_list_lock);

	ret = crypto_रेजिस्टर_kpp(&aपंचांगel_ecdh_nist_p256);
	अगर (ret) अणु
		spin_lock(&driver_data.i2c_list_lock);
		list_del(&i2c_priv->i2c_client_list_node);
		spin_unlock(&driver_data.i2c_list_lock);

		dev_err(&client->dev, "%s alg registration failed\n",
			aपंचांगel_ecdh_nist_p256.base.cra_driver_name);
	पूर्ण अन्यथा अणु
		dev_info(&client->dev, "atmel ecc algorithms registered in /proc/crypto\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_ecc_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);

	/* Return EBUSY अगर i2c client alपढ़ोy allocated. */
	अगर (atomic_पढ़ो(&i2c_priv->tfm_count)) अणु
		dev_err(&client->dev, "Device is busy\n");
		वापस -EBUSY;
	पूर्ण

	crypto_unरेजिस्टर_kpp(&aपंचांगel_ecdh_nist_p256);

	spin_lock(&driver_data.i2c_list_lock);
	list_del(&i2c_priv->i2c_client_list_node);
	spin_unlock(&driver_data.i2c_list_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id aपंचांगel_ecc_dt_ids[] = अणु
	अणु
		.compatible = "atmel,atecc508a",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_ecc_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id aपंचांगel_ecc_id[] = अणु
	अणु "atecc508a", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aपंचांगel_ecc_id);

अटल काष्ठा i2c_driver aपंचांगel_ecc_driver = अणु
	.driver = अणु
		.name	= "atmel-ecc",
		.of_match_table = of_match_ptr(aपंचांगel_ecc_dt_ids),
	पूर्ण,
	.probe		= aपंचांगel_ecc_probe,
	.हटाओ		= aपंचांगel_ecc_हटाओ,
	.id_table	= aपंचांगel_ecc_id,
पूर्ण;

अटल पूर्णांक __init aपंचांगel_ecc_init(व्योम)
अणु
	spin_lock_init(&driver_data.i2c_list_lock);
	INIT_LIST_HEAD(&driver_data.i2c_client_list);
	वापस i2c_add_driver(&aपंचांगel_ecc_driver);
पूर्ण

अटल व्योम __निकास aपंचांगel_ecc_निकास(व्योम)
अणु
	flush_scheduled_work();
	i2c_del_driver(&aपंचांगel_ecc_driver);
पूर्ण

module_init(aपंचांगel_ecc_init);
module_निकास(aपंचांगel_ecc_निकास);

MODULE_AUTHOR("Tudor Ambarus <tudor.ambarus@microchip.com>");
MODULE_DESCRIPTION("Microchip / Atmel ECC (I2C) driver");
MODULE_LICENSE("GPL v2");
