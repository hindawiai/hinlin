<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 Arm Ltd.

#समावेश <linux/arm-smccc.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_emulate.h>

#समावेश <kvm/arm_hypercalls.h>

#घोषणा ARM_SMCCC_TRNG_VERSION_1_0	0x10000UL

/* Those values are deliberately separate from the generic SMCCC definitions. */
#घोषणा TRNG_SUCCESS			0UL
#घोषणा TRNG_NOT_SUPPORTED		((अचिन्हित दीर्घ)-1)
#घोषणा TRNG_INVALID_PARAMETER		((अचिन्हित दीर्घ)-2)
#घोषणा TRNG_NO_ENTROPY			((अचिन्हित दीर्घ)-3)

#घोषणा TRNG_MAX_BITS64			192

अटल स्थिर uuid_t arm_smc_trng_uuid __aligned(4) = UUID_INIT(
	0x0d21e000, 0x4384, 0x11eb, 0x80, 0x70, 0x52, 0x44, 0x55, 0x4e, 0x5a, 0x4c);

अटल पूर्णांक kvm_trng_करो_rnd(काष्ठा kvm_vcpu *vcpu, पूर्णांक size)
अणु
	DECLARE_BITMAP(bits, TRNG_MAX_BITS64);
	u32 num_bits = smccc_get_arg1(vcpu);
	पूर्णांक i;

	अगर (num_bits > 3 * size) अणु
		smccc_set_retval(vcpu, TRNG_INVALID_PARAMETER, 0, 0, 0);
		वापस 1;
	पूर्ण

	/* get as many bits as we need to fulfil the request */
	क्रम (i = 0; i < DIV_ROUND_UP(num_bits, BITS_PER_LONG); i++)
		bits[i] = get_अक्रमom_दीर्घ();

	biपंचांगap_clear(bits, num_bits, TRNG_MAX_BITS64 - num_bits);

	अगर (size == 32)
		smccc_set_retval(vcpu, TRNG_SUCCESS, lower_32_bits(bits[1]),
				 upper_32_bits(bits[0]), lower_32_bits(bits[0]));
	अन्यथा
		smccc_set_retval(vcpu, TRNG_SUCCESS, bits[2], bits[1], bits[0]);

	memzero_explicit(bits, माप(bits));
	वापस 1;
पूर्ण

पूर्णांक kvm_trng_call(काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर __le32 *u = (__le32 *)arm_smc_trng_uuid.b;
	u32 func_id = smccc_get_function(vcpu);
	अचिन्हित दीर्घ val = TRNG_NOT_SUPPORTED;
	पूर्णांक size = 64;

	चयन (func_id) अणु
	हाल ARM_SMCCC_TRNG_VERSION:
		val = ARM_SMCCC_TRNG_VERSION_1_0;
		अवरोध;
	हाल ARM_SMCCC_TRNG_FEATURES:
		चयन (smccc_get_arg1(vcpu)) अणु
		हाल ARM_SMCCC_TRNG_VERSION:
		हाल ARM_SMCCC_TRNG_FEATURES:
		हाल ARM_SMCCC_TRNG_GET_UUID:
		हाल ARM_SMCCC_TRNG_RND32:
		हाल ARM_SMCCC_TRNG_RND64:
			val = TRNG_SUCCESS;
		पूर्ण
		अवरोध;
	हाल ARM_SMCCC_TRNG_GET_UUID:
		smccc_set_retval(vcpu, le32_to_cpu(u[0]), le32_to_cpu(u[1]),
				 le32_to_cpu(u[2]), le32_to_cpu(u[3]));
		वापस 1;
	हाल ARM_SMCCC_TRNG_RND32:
		size = 32;
		fallthrough;
	हाल ARM_SMCCC_TRNG_RND64:
		वापस kvm_trng_करो_rnd(vcpu, size);
	पूर्ण

	smccc_set_retval(vcpu, val, 0, 0, 0);
	वापस 1;
पूर्ण
