<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 Linaro Ltd;  <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

प्रकार जोड़ efi_rng_protocol efi_rng_protocol_t;

जोड़ efi_rng_protocol अणु
	काष्ठा अणु
		efi_status_t (__efiapi *get_info)(efi_rng_protocol_t *,
						  अचिन्हित दीर्घ *,
						  efi_guid_t *);
		efi_status_t (__efiapi *get_rng)(efi_rng_protocol_t *,
						 efi_guid_t *, अचिन्हित दीर्घ,
						 u8 *out);
	पूर्ण;
	काष्ठा अणु
		u32 get_info;
		u32 get_rng;
	पूर्ण mixed_mode;
पूर्ण;

/**
 * efi_get_अक्रमom_bytes() - fill a buffer with अक्रमom bytes
 * @size:	size of the buffer
 * @out:	caller allocated buffer to receive the अक्रमom bytes
 *
 * The call will fail अगर either the firmware करोes not implement the
 * EFI_RNG_PROTOCOL or there are not enough अक्रमom bytes available to fill
 * the buffer.
 *
 * Return:	status code
 */
efi_status_t efi_get_अक्रमom_bytes(अचिन्हित दीर्घ size, u8 *out)
अणु
	efi_guid_t rng_proto = EFI_RNG_PROTOCOL_GUID;
	efi_status_t status;
	efi_rng_protocol_t *rng = शून्य;

	status = efi_bs_call(locate_protocol, &rng_proto, शून्य, (व्योम **)&rng);
	अगर (status != EFI_SUCCESS)
		वापस status;

	वापस efi_call_proto(rng, get_rng, शून्य, size, out);
पूर्ण

/**
 * efi_अक्रमom_get_seed() - provide अक्रमom seed as configuration table
 *
 * The EFI_RNG_PROTOCOL is used to पढ़ो अक्रमom bytes. These अक्रमom bytes are
 * saved as a configuration table which can be used as entropy by the kernel
 * क्रम the initialization of its pseuकरो अक्रमom number generator.
 *
 * If the EFI_RNG_PROTOCOL is not available or there are not enough अक्रमom bytes
 * available, the configuration table will not be installed and an error code
 * will be वापसed.
 *
 * Return:	status code
 */
efi_status_t efi_अक्रमom_get_seed(व्योम)
अणु
	efi_guid_t rng_proto = EFI_RNG_PROTOCOL_GUID;
	efi_guid_t rng_algo_raw = EFI_RNG_ALGORITHM_RAW;
	efi_guid_t rng_table_guid = LINUX_EFI_RANDOM_SEED_TABLE_GUID;
	efi_rng_protocol_t *rng = शून्य;
	काष्ठा linux_efi_अक्रमom_seed *seed = शून्य;
	efi_status_t status;

	status = efi_bs_call(locate_protocol, &rng_proto, शून्य, (व्योम **)&rng);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_bs_call(allocate_pool, EFI_RUNTIME_SERVICES_DATA,
			     माप(*seed) + EFI_RANDOM_SEED_SIZE,
			     (व्योम **)&seed);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_call_proto(rng, get_rng, &rng_algo_raw,
				 EFI_RANDOM_SEED_SIZE, seed->bits);

	अगर (status == EFI_UNSUPPORTED)
		/*
		 * Use whatever algorithm we have available अगर the raw algorithm
		 * is not implemented.
		 */
		status = efi_call_proto(rng, get_rng, शून्य,
					EFI_RANDOM_SEED_SIZE, seed->bits);

	अगर (status != EFI_SUCCESS)
		जाओ err_मुक्तpool;

	seed->size = EFI_RANDOM_SEED_SIZE;
	status = efi_bs_call(install_configuration_table, &rng_table_guid, seed);
	अगर (status != EFI_SUCCESS)
		जाओ err_मुक्तpool;

	वापस EFI_SUCCESS;

err_मुक्तpool:
	efi_bs_call(मुक्त_pool, seed);
	वापस status;
पूर्ण
