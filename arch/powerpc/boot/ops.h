<शैली गुरु>
/*
 * Global definition of all the bootwrapper operations.
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 *
 * 2006 (c) MontaVista Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित _PPC_BOOT_OPS_H_
#घोषणा _PPC_BOOT_OPS_H_

#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "string.h"

#घोषणा	BOOT_COMMAND_LINE_SIZE	2048
#घोषणा	MAX_PATH_LEN		256
#घोषणा	MAX_PROP_LEN		256 /* What should this be? */

प्रकार व्योम (*kernel_entry_t)(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, व्योम *r5);

/* Platक्रमm specअगरic operations */
काष्ठा platक्रमm_ops अणु
	व्योम	(*fixups)(व्योम);
	व्योम	(*image_hdr)(स्थिर व्योम *);
	व्योम *	(*दो_स्मृति)(अचिन्हित दीर्घ size);
	व्योम	(*मुक्त)(व्योम *ptr);
	व्योम *	(*पुनः_स्मृति)(व्योम *ptr, अचिन्हित दीर्घ size);
	व्योम	(*निकास)(व्योम);
	व्योम *	(*vmlinux_alloc)(अचिन्हित दीर्घ size);
	व्योम  	(*kentry)(अचिन्हित दीर्घ fdt_addr, व्योम *vmlinux_addr);
पूर्ण;
बाह्य काष्ठा platक्रमm_ops platक्रमm_ops;

/* Device Tree operations */
काष्ठा dt_ops अणु
	व्योम *	(*finddevice)(स्थिर अक्षर *name);
	पूर्णांक	(*getprop)(स्थिर व्योम *phandle, स्थिर अक्षर *name, व्योम *buf,
			स्थिर पूर्णांक buflen);
	पूर्णांक	(*setprop)(स्थिर व्योम *phandle, स्थिर अक्षर *name,
			स्थिर व्योम *buf, स्थिर पूर्णांक buflen);
	पूर्णांक (*del_node)(स्थिर व्योम *phandle);
	व्योम *(*get_parent)(स्थिर व्योम *phandle);
	/* The node must not alपढ़ोy exist. */
	व्योम *(*create_node)(स्थिर व्योम *parent, स्थिर अक्षर *name);
	व्योम *(*find_node_by_prop_value)(स्थिर व्योम *prev,
	                                 स्थिर अक्षर *propname,
	                                 स्थिर अक्षर *propval, पूर्णांक proplen);
	व्योम *(*find_node_by_compatible)(स्थिर व्योम *prev,
	                                 स्थिर अक्षर *compat);
	अचिन्हित दीर्घ (*finalize)(व्योम);
	अक्षर *(*get_path)(स्थिर व्योम *phandle, अक्षर *buf, पूर्णांक len);
पूर्ण;
बाह्य काष्ठा dt_ops dt_ops;

/* Console operations */
काष्ठा console_ops अणु
	पूर्णांक	(*खोलो)(व्योम);
	व्योम	(*ग_लिखो)(स्थिर अक्षर *buf, पूर्णांक len);
	व्योम	(*edit_cmdline)(अक्षर *buf, पूर्णांक len, अचिन्हित पूर्णांक getline_समयout);
	व्योम	(*बंद)(व्योम);
	व्योम	*data;
पूर्ण;
बाह्य काष्ठा console_ops console_ops;

/* Serial console operations */
काष्ठा serial_console_data अणु
	पूर्णांक		(*खोलो)(व्योम);
	व्योम		(*अ_दो)(अचिन्हित अक्षर c);
	अचिन्हित अक्षर	(*अ_लो)(व्योम);
	u8		(*tstc)(व्योम);
	व्योम		(*बंद)(व्योम);
पूर्ण;

काष्ठा loader_info अणु
	व्योम *promptr;
	अचिन्हित दीर्घ initrd_addr, initrd_size;
	अक्षर *cmdline;
	पूर्णांक cmdline_len;
पूर्ण;
बाह्य काष्ठा loader_info loader_info;

व्योम start(व्योम);
व्योम fdt_init(व्योम *blob);
पूर्णांक serial_console_init(व्योम);
पूर्णांक ns16550_console_init(व्योम *devp, काष्ठा serial_console_data *scdp);
पूर्णांक cpm_console_init(व्योम *devp, काष्ठा serial_console_data *scdp);
पूर्णांक mpc5200_psc_console_init(व्योम *devp, काष्ठा serial_console_data *scdp);
पूर्णांक opal_console_init(व्योम *devp, काष्ठा serial_console_data *scdp);
व्योम *simple_alloc_init(अक्षर *base, अचिन्हित दीर्घ heap_size,
			अचिन्हित दीर्घ granularity, अचिन्हित दीर्घ max_allocs);
बाह्य व्योम flush_cache(व्योम *, अचिन्हित दीर्घ);
पूर्णांक dt_xlate_reg(व्योम *node, पूर्णांक res, अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ *size);
पूर्णांक dt_xlate_addr(व्योम *node, u32 *buf, पूर्णांक buflen, अचिन्हित दीर्घ *xlated_addr);
पूर्णांक dt_is_compatible(व्योम *node, स्थिर अक्षर *compat);
व्योम dt_get_reg_क्रमmat(व्योम *node, u32 *naddr, u32 *nsize);
पूर्णांक dt_get_भव_reg(व्योम *node, व्योम **addr, पूर्णांक nres);

अटल अंतरभूत व्योम *finddevice(स्थिर अक्षर *name)
अणु
	वापस (dt_ops.finddevice) ? dt_ops.finddevice(name) : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक getprop(व्योम *devp, स्थिर अक्षर *name, व्योम *buf, पूर्णांक buflen)
अणु
	वापस (dt_ops.getprop) ? dt_ops.getprop(devp, name, buf, buflen) : -1;
पूर्ण

अटल अंतरभूत पूर्णांक setprop(व्योम *devp, स्थिर अक्षर *name,
                          स्थिर व्योम *buf, पूर्णांक buflen)
अणु
	वापस (dt_ops.setprop) ? dt_ops.setprop(devp, name, buf, buflen) : -1;
पूर्ण
#घोषणा setprop_val(devp, name, val) \
	करो अणु \
		typeof(val) x = (val); \
		setprop((devp), (name), &x, माप(x)); \
	पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक setprop_str(व्योम *devp, स्थिर अक्षर *name, स्थिर अक्षर *buf)
अणु
	अगर (dt_ops.setprop)
		वापस dt_ops.setprop(devp, name, buf, म_माप(buf) + 1);

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक del_node(स्थिर व्योम *devp)
अणु
	वापस dt_ops.del_node ? dt_ops.del_node(devp) : -1;
पूर्ण

अटल अंतरभूत व्योम *get_parent(स्थिर अक्षर *devp)
अणु
	वापस dt_ops.get_parent ? dt_ops.get_parent(devp) : शून्य;
पूर्ण

अटल अंतरभूत व्योम *create_node(स्थिर व्योम *parent, स्थिर अक्षर *name)
अणु
	वापस dt_ops.create_node ? dt_ops.create_node(parent, name) : शून्य;
पूर्ण


अटल अंतरभूत व्योम *find_node_by_prop_value(स्थिर व्योम *prev,
                                            स्थिर अक्षर *propname,
                                            स्थिर अक्षर *propval, पूर्णांक proplen)
अणु
	अगर (dt_ops.find_node_by_prop_value)
		वापस dt_ops.find_node_by_prop_value(prev, propname,
		                                      propval, proplen);

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *find_node_by_prop_value_str(स्थिर व्योम *prev,
                                                स्थिर अक्षर *propname,
                                                स्थिर अक्षर *propval)
अणु
	वापस find_node_by_prop_value(prev, propname, propval,
	                               म_माप(propval) + 1);
पूर्ण

अटल अंतरभूत व्योम *find_node_by_devtype(स्थिर व्योम *prev,
                                         स्थिर अक्षर *type)
अणु
	वापस find_node_by_prop_value_str(prev, "device_type", type);
पूर्ण

अटल अंतरभूत व्योम *find_node_by_alias(स्थिर अक्षर *alias)
अणु
	व्योम *devp = finddevice("/aliases");

	अगर (devp) अणु
		अक्षर path[MAX_PATH_LEN];
		अगर (getprop(devp, alias, path, MAX_PATH_LEN) > 0)
			वापस finddevice(path);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *find_node_by_compatible(स्थिर व्योम *prev,
                                            स्थिर अक्षर *compat)
अणु
	अगर (dt_ops.find_node_by_compatible)
		वापस dt_ops.find_node_by_compatible(prev, compat);

	वापस शून्य;
पूर्ण

व्योम dt_fixup_memory(u64 start, u64 size);
व्योम dt_fixup_cpu_घड़ीs(u32 cpufreq, u32 tbfreq, u32 busfreq);
व्योम dt_fixup_घड़ी(स्थिर अक्षर *path, u32 freq);
व्योम dt_fixup_mac_address_by_alias(स्थिर अक्षर *alias, स्थिर u8 *addr);
व्योम dt_fixup_mac_address(u32 index, स्थिर u8 *addr);
व्योम __dt_fixup_mac_addresses(u32 startindex, ...);
#घोषणा dt_fixup_mac_addresses(...) \
	__dt_fixup_mac_addresses(0, __VA_ARGS__, शून्य)


अटल अंतरभूत व्योम *find_node_by_linuxphandle(स्थिर u32 linuxphandle)
अणु
	वापस find_node_by_prop_value(शून्य, "linux,phandle",
			(अक्षर *)&linuxphandle, माप(u32));
पूर्ण

अटल अंतरभूत अक्षर *get_path(स्थिर व्योम *phandle, अक्षर *buf, पूर्णांक len)
अणु
	अगर (dt_ops.get_path)
		वापस dt_ops.get_path(phandle, buf, len);

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *दो_स्मृति(अचिन्हित दीर्घ size)
अणु
	वापस (platक्रमm_ops.दो_स्मृति) ? platक्रमm_ops.दो_स्मृति(size) : शून्य;
पूर्ण

अटल अंतरभूत व्योम मुक्त(व्योम *ptr)
अणु
	अगर (platक्रमm_ops.मुक्त)
		platक्रमm_ops.मुक्त(ptr);
पूर्ण

अटल अंतरभूत व्योम निकास(व्योम)
अणु
	अगर (platक्रमm_ops.निकास)
		platक्रमm_ops.निकास();
	क्रम(;;);
पूर्ण
#घोषणा fatal(args...) अणु म_लिखो(args); निकास(); पूर्ण


#घोषणा BSS_STACK(size) \
	अटल अक्षर _bss_stack[size]; \
	व्योम *_platक्रमm_stack_top = _bss_stack + माप(_bss_stack);

बाह्य अचिन्हित दीर्घ समयbase_period_ns;
व्योम udelay(दीर्घ delay);

बाह्य अक्षर _start[];
बाह्य अक्षर __bss_start[];
बाह्य अक्षर _end[];
बाह्य अक्षर _vmlinux_start[];
बाह्य अक्षर _vmlinux_end[];
बाह्य अक्षर _initrd_start[];
बाह्य अक्षर _initrd_end[];
बाह्य अक्षर _dtb_start[];
बाह्य अक्षर _dtb_end[];
बाह्य अक्षर _esm_blob_start[];
बाह्य अक्षर _esm_blob_end[];

अटल अंतरभूत __attribute__((स्थिर))
पूर्णांक __ilog2_u32(u32 n)
अणु
	पूर्णांक bit;
	यंत्र ("cntlzw %0,%1" : "=r" (bit) : "r" (n));
	वापस 31 - bit;
पूर्ण

दीर्घ partial_decompress(व्योम *inbuf, अचिन्हित दीर्घ input_size, व्योम *outbuf,
	अचिन्हित दीर्घ output_size, अचिन्हित दीर्घ skip);

#पूर्ण_अगर /* _PPC_BOOT_OPS_H_ */
