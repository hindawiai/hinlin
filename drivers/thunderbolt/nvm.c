<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NVM helpers
 *
 * Copyright (C) 2020, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "tb.h"

अटल DEFINE_IDA(nvm_ida);

/**
 * tb_nvm_alloc() - Allocate new NVM काष्ठाure
 * @dev: Device owning the NVM
 *
 * Allocates new NVM काष्ठाure with unique @id and वापसs it. In हाल
 * of error वापसs ERR_PTR().
 */
काष्ठा tb_nvm *tb_nvm_alloc(काष्ठा device *dev)
अणु
	काष्ठा tb_nvm *nvm;
	पूर्णांक ret;

	nvm = kzalloc(माप(*nvm), GFP_KERNEL);
	अगर (!nvm)
		वापस ERR_PTR(-ENOMEM);

	ret = ida_simple_get(&nvm_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0) अणु
		kमुक्त(nvm);
		वापस ERR_PTR(ret);
	पूर्ण

	nvm->id = ret;
	nvm->dev = dev;

	वापस nvm;
पूर्ण

/**
 * tb_nvm_add_active() - Adds active NVMem device to NVM
 * @nvm: NVM काष्ठाure
 * @size: Size of the active NVM in bytes
 * @reg_पढ़ो: Poपूर्णांकer to the function to पढ़ो the NVM (passed directly to the
 *	      NVMem device)
 *
 * Registers new active NVmem device क्रम @nvm. The @reg_पढ़ो is called
 * directly from NVMem so it must handle possible concurrent access अगर
 * needed. The first parameter passed to @reg_पढ़ो is @nvm काष्ठाure.
 * Returns %0 in success and negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_nvm_add_active(काष्ठा tb_nvm *nvm, माप_प्रकार size, nvmem_reg_पढ़ो_t reg_पढ़ो)
अणु
	काष्ठा nvmem_config config;
	काष्ठा nvmem_device *nvmem;

	स_रखो(&config, 0, माप(config));

	config.name = "nvm_active";
	config.reg_पढ़ो = reg_पढ़ो;
	config.पढ़ो_only = true;
	config.id = nvm->id;
	config.stride = 4;
	config.word_size = 4;
	config.size = size;
	config.dev = nvm->dev;
	config.owner = THIS_MODULE;
	config.priv = nvm;

	nvmem = nvmem_रेजिस्टर(&config);
	अगर (IS_ERR(nvmem))
		वापस PTR_ERR(nvmem);

	nvm->active = nvmem;
	वापस 0;
पूर्ण

/**
 * tb_nvm_ग_लिखो_buf() - Write data to @nvm buffer
 * @nvm: NVM काष्ठाure
 * @offset: Offset where to ग_लिखो the data
 * @val: Data buffer to ग_लिखो
 * @bytes: Number of bytes to ग_लिखो
 *
 * Helper function to cache the new NVM image beक्रमe it is actually
 * written to the flash. Copies @bytes from @val to @nvm->buf starting
 * from @offset.
 */
पूर्णांक tb_nvm_ग_लिखो_buf(काष्ठा tb_nvm *nvm, अचिन्हित पूर्णांक offset, व्योम *val,
		     माप_प्रकार bytes)
अणु
	अगर (!nvm->buf) अणु
		nvm->buf = vदो_स्मृति(NVM_MAX_SIZE);
		अगर (!nvm->buf)
			वापस -ENOMEM;
	पूर्ण

	nvm->flushed = false;
	nvm->buf_data_size = offset + bytes;
	स_नकल(nvm->buf + offset, val, bytes);
	वापस 0;
पूर्ण

/**
 * tb_nvm_add_non_active() - Adds non-active NVMem device to NVM
 * @nvm: NVM काष्ठाure
 * @size: Size of the non-active NVM in bytes
 * @reg_ग_लिखो: Poपूर्णांकer to the function to ग_लिखो the NVM (passed directly
 *	       to the NVMem device)
 *
 * Registers new non-active NVmem device क्रम @nvm. The @reg_ग_लिखो is called
 * directly from NVMem so it must handle possible concurrent access अगर
 * needed. The first parameter passed to @reg_ग_लिखो is @nvm काष्ठाure.
 * Returns %0 in success and negative त्रुटि_सं otherwise.
 */
पूर्णांक tb_nvm_add_non_active(काष्ठा tb_nvm *nvm, माप_प्रकार size,
			  nvmem_reg_ग_लिखो_t reg_ग_लिखो)
अणु
	काष्ठा nvmem_config config;
	काष्ठा nvmem_device *nvmem;

	स_रखो(&config, 0, माप(config));

	config.name = "nvm_non_active";
	config.reg_ग_लिखो = reg_ग_लिखो;
	config.root_only = true;
	config.id = nvm->id;
	config.stride = 4;
	config.word_size = 4;
	config.size = size;
	config.dev = nvm->dev;
	config.owner = THIS_MODULE;
	config.priv = nvm;

	nvmem = nvmem_रेजिस्टर(&config);
	अगर (IS_ERR(nvmem))
		वापस PTR_ERR(nvmem);

	nvm->non_active = nvmem;
	वापस 0;
पूर्ण

/**
 * tb_nvm_मुक्त() - Release NVM and its resources
 * @nvm: NVM काष्ठाure to release
 *
 * Releases NVM and the NVMem devices अगर they were रेजिस्टरed.
 */
व्योम tb_nvm_मुक्त(काष्ठा tb_nvm *nvm)
अणु
	अगर (nvm) अणु
		अगर (nvm->non_active)
			nvmem_unरेजिस्टर(nvm->non_active);
		अगर (nvm->active)
			nvmem_unरेजिस्टर(nvm->active);
		vमुक्त(nvm->buf);
		ida_simple_हटाओ(&nvm_ida, nvm->id);
	पूर्ण
	kमुक्त(nvm);
पूर्ण

व्योम tb_nvm_निकास(व्योम)
अणु
	ida_destroy(&nvm_ida);
पूर्ण
