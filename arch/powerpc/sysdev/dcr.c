<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (c) Copyright 2006 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/dcr.h>

#अगर_घोषित CONFIG_PPC_DCR_MMIO
अटल काष्ठा device_node *find_dcr_parent(काष्ठा device_node *node)
अणु
	काष्ठा device_node *par, *पंचांगp;
	स्थिर u32 *p;

	क्रम (par = of_node_get(node); par;) अणु
		अगर (of_get_property(par, "dcr-controller", शून्य))
			अवरोध;
		p = of_get_property(par, "dcr-parent", शून्य);
		पंचांगp = par;
		अगर (p == शून्य)
			par = of_get_parent(par);
		अन्यथा
			par = of_find_node_by_phandle(*p);
		of_node_put(पंचांगp);
	पूर्ण
	वापस par;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_DCR_NATIVE) && defined(CONFIG_PPC_DCR_MMIO)

bool dcr_map_ok_generic(dcr_host_t host)
अणु
	अगर (host.type == DCR_HOST_NATIVE)
		वापस dcr_map_ok_native(host.host.native);
	अन्यथा अगर (host.type == DCR_HOST_MMIO)
		वापस dcr_map_ok_mmio(host.host.mmio);
	अन्यथा
		वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(dcr_map_ok_generic);

dcr_host_t dcr_map_generic(काष्ठा device_node *dev,
			   अचिन्हित पूर्णांक dcr_n,
			   अचिन्हित पूर्णांक dcr_c)
अणु
	dcr_host_t host;
	काष्ठा device_node *dp;
	स्थिर अक्षर *prop;

	host.type = DCR_HOST_INVALID;

	dp = find_dcr_parent(dev);
	अगर (dp == शून्य)
		वापस host;

	prop = of_get_property(dp, "dcr-access-method", शून्य);

	pr_debug("dcr_map_generic(dcr-access-method = %s)\n", prop);

	अगर (!म_भेद(prop, "native")) अणु
		host.type = DCR_HOST_NATIVE;
		host.host.native = dcr_map_native(dev, dcr_n, dcr_c);
	पूर्ण अन्यथा अगर (!म_भेद(prop, "mmio")) अणु
		host.type = DCR_HOST_MMIO;
		host.host.mmio = dcr_map_mmio(dev, dcr_n, dcr_c);
	पूर्ण

	of_node_put(dp);
	वापस host;
पूर्ण
EXPORT_SYMBOL_GPL(dcr_map_generic);

व्योम dcr_unmap_generic(dcr_host_t host, अचिन्हित पूर्णांक dcr_c)
अणु
	अगर (host.type == DCR_HOST_NATIVE)
		dcr_unmap_native(host.host.native, dcr_c);
	अन्यथा अगर (host.type == DCR_HOST_MMIO)
		dcr_unmap_mmio(host.host.mmio, dcr_c);
	अन्यथा /* host.type == DCR_HOST_INVALID */
		WARN_ON(true);
पूर्ण
EXPORT_SYMBOL_GPL(dcr_unmap_generic);

u32 dcr_पढ़ो_generic(dcr_host_t host, अचिन्हित पूर्णांक dcr_n)
अणु
	अगर (host.type == DCR_HOST_NATIVE)
		वापस dcr_पढ़ो_native(host.host.native, dcr_n);
	अन्यथा अगर (host.type == DCR_HOST_MMIO)
		वापस dcr_पढ़ो_mmio(host.host.mmio, dcr_n);
	अन्यथा /* host.type == DCR_HOST_INVALID */
		WARN_ON(true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dcr_पढ़ो_generic);

व्योम dcr_ग_लिखो_generic(dcr_host_t host, अचिन्हित पूर्णांक dcr_n, u32 value)
अणु
	अगर (host.type == DCR_HOST_NATIVE)
		dcr_ग_लिखो_native(host.host.native, dcr_n, value);
	अन्यथा अगर (host.type == DCR_HOST_MMIO)
		dcr_ग_लिखो_mmio(host.host.mmio, dcr_n, value);
	अन्यथा /* host.type == DCR_HOST_INVALID */
		WARN_ON(true);
पूर्ण
EXPORT_SYMBOL_GPL(dcr_ग_लिखो_generic);

#पूर्ण_अगर /* defined(CONFIG_PPC_DCR_NATIVE) && defined(CONFIG_PPC_DCR_MMIO) */

अचिन्हित पूर्णांक dcr_resource_start(स्थिर काष्ठा device_node *np,
				अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक ds;
	स्थिर u32 *dr = of_get_property(np, "dcr-reg", &ds);

	अगर (dr == शून्य || ds & 1 || index >= (ds / 8))
		वापस 0;

	वापस dr[index * 2];
पूर्ण
EXPORT_SYMBOL_GPL(dcr_resource_start);

अचिन्हित पूर्णांक dcr_resource_len(स्थिर काष्ठा device_node *np, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक ds;
	स्थिर u32 *dr = of_get_property(np, "dcr-reg", &ds);

	अगर (dr == शून्य || ds & 1 || index >= (ds / 8))
		वापस 0;

	वापस dr[index * 2 + 1];
पूर्ण
EXPORT_SYMBOL_GPL(dcr_resource_len);

#अगर_घोषित CONFIG_PPC_DCR_MMIO

अटल u64 of_translate_dcr_address(काष्ठा device_node *dev,
				    अचिन्हित पूर्णांक dcr_n,
				    अचिन्हित पूर्णांक *out_stride)
अणु
	काष्ठा device_node *dp;
	स्थिर u32 *p;
	अचिन्हित पूर्णांक stride;
	u64 ret = OF_BAD_ADDR;

	dp = find_dcr_parent(dev);
	अगर (dp == शून्य)
		वापस OF_BAD_ADDR;

	/* Stride is not properly defined yet, शेष to 0x10 क्रम Axon */
	p = of_get_property(dp, "dcr-mmio-stride", शून्य);
	stride = (p == शून्य) ? 0x10 : *p;

	/* XXX FIXME: Which property name is to use of the 2 following ? */
	p = of_get_property(dp, "dcr-mmio-range", शून्य);
	अगर (p == शून्य)
		p = of_get_property(dp, "dcr-mmio-space", शून्य);
	अगर (p == शून्य)
		जाओ करोne;

	/* Maybe could करो some better range checking here */
	ret = of_translate_address(dp, p);
	अगर (ret != OF_BAD_ADDR)
		ret += (u64)(stride) * (u64)dcr_n;
	अगर (out_stride)
		*out_stride = stride;

 करोne:
	of_node_put(dp);
	वापस ret;
पूर्ण

dcr_host_mmio_t dcr_map_mmio(काष्ठा device_node *dev,
			     अचिन्हित पूर्णांक dcr_n,
			     अचिन्हित पूर्णांक dcr_c)
अणु
	dcr_host_mmio_t ret = अणु .token = शून्य, .stride = 0, .base = dcr_n पूर्ण;
	u64 addr;

	pr_debug("dcr_map(%pOF, 0x%x, 0x%x)\n",
		 dev, dcr_n, dcr_c);

	addr = of_translate_dcr_address(dev, dcr_n, &ret.stride);
	pr_debug("translates to addr: 0x%llx, stride: 0x%x\n",
		 (अचिन्हित दीर्घ दीर्घ) addr, ret.stride);
	अगर (addr == OF_BAD_ADDR)
		वापस ret;
	pr_debug("mapping 0x%x bytes\n", dcr_c * ret.stride);
	ret.token = ioremap(addr, dcr_c * ret.stride);
	अगर (ret.token == शून्य)
		वापस ret;
	pr_debug("mapped at 0x%p -> base is 0x%p\n",
		 ret.token, ret.token - dcr_n * ret.stride);
	ret.token -= dcr_n * ret.stride;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dcr_map_mmio);

व्योम dcr_unmap_mmio(dcr_host_mmio_t host, अचिन्हित पूर्णांक dcr_c)
अणु
	dcr_host_mmio_t h = host;

	अगर (h.token == शून्य)
		वापस;
	h.token += host.base * h.stride;
	iounmap(h.token);
	h.token = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(dcr_unmap_mmio);

#पूर्ण_अगर /* defined(CONFIG_PPC_DCR_MMIO) */

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
DEFINE_SPINLOCK(dcr_ind_lock);
EXPORT_SYMBOL_GPL(dcr_ind_lock);
#पूर्ण_अगर	/* defined(CONFIG_PPC_DCR_NATIVE) */

