<शैली गुरु>
/* Copyright 2017 NXP Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of NXP Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NXP Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/dma-mapping.h>
#समावेश "dpaa_sys.h"

/*
 * Initialize a devices निजी memory region
 */
पूर्णांक qbman_init_निजी_mem(काष्ठा device *dev, पूर्णांक idx, dma_addr_t *addr,
				माप_प्रकार *size)
अणु
	काष्ठा device_node *mem_node;
	काष्ठा reserved_mem *rmem;
	काष्ठा property *prop;
	पूर्णांक len, err;
	__be32 *res_array;

	mem_node = of_parse_phandle(dev->of_node, "memory-region", idx);
	अगर (!mem_node) अणु
		dev_err(dev, "No memory-region found for index %d\n", idx);
		वापस -ENODEV;
	पूर्ण

	rmem = of_reserved_mem_lookup(mem_node);
	अगर (!rmem) अणु
		dev_err(dev, "of_reserved_mem_lookup() returned NULL\n");
		वापस -ENODEV;
	पूर्ण
	*addr = rmem->base;
	*size = rmem->size;

	/*
	 * Check अगर the reg property exists - अगर not insert the node
	 * so upon kexec() the same memory region address will be preserved.
	 * This is needed because QBMan HW करोes not allow the base address/
	 * size to be modअगरied once set.
	 */
	prop = of_find_property(mem_node, "reg", &len);
	अगर (!prop) अणु
		prop = devm_kzalloc(dev, माप(*prop), GFP_KERNEL);
		अगर (!prop)
			वापस -ENOMEM;
		prop->value = res_array = devm_kzalloc(dev, माप(__be32) * 4,
						       GFP_KERNEL);
		अगर (!prop->value)
			वापस -ENOMEM;
		res_array[0] = cpu_to_be32(upper_32_bits(*addr));
		res_array[1] = cpu_to_be32(lower_32_bits(*addr));
		res_array[2] = cpu_to_be32(upper_32_bits(*size));
		res_array[3] = cpu_to_be32(lower_32_bits(*size));
		prop->length = माप(__be32) * 4;
		prop->name = devm_kstrdup(dev, "reg", GFP_KERNEL);
		अगर (!prop->name)
			वापस -ENOMEM;
		err = of_add_property(mem_node, prop);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
