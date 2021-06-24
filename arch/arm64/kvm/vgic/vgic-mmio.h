<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */
#अगर_अघोषित __KVM_ARM_VGIC_MMIO_H__
#घोषणा __KVM_ARM_VGIC_MMIO_H__

काष्ठा vgic_रेजिस्टर_region अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक bits_per_irq;
	अचिन्हित पूर्णांक access_flags;
	जोड़ अणु
		अचिन्हित दीर्घ (*पढ़ो)(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
				      अचिन्हित पूर्णांक len);
		अचिन्हित दीर्घ (*its_पढ़ो)(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
					  gpa_t addr, अचिन्हित पूर्णांक len);
	पूर्ण;
	जोड़ अणु
		व्योम (*ग_लिखो)(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			      अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val);
		व्योम (*its_ग_लिखो)(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				  gpa_t addr, अचिन्हित पूर्णांक len,
				  अचिन्हित दीर्घ val);
	पूर्ण;
	अचिन्हित दीर्घ (*uaccess_पढ़ो)(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
				      अचिन्हित पूर्णांक len);
	जोड़ अणु
		पूर्णांक (*uaccess_ग_लिखो)(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
				     अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val);
		पूर्णांक (*uaccess_its_ग_लिखो)(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
					 gpa_t addr, अचिन्हित पूर्णांक len,
					 अचिन्हित दीर्घ val);
	पूर्ण;
पूर्ण;

बाह्य काष्ठा kvm_io_device_ops kvm_io_gic_ops;

#घोषणा VGIC_ACCESS_8bit	1
#घोषणा VGIC_ACCESS_32bit	2
#घोषणा VGIC_ACCESS_64bit	4

/*
 * Generate a mask that covers the number of bytes required to address
 * up to 1024 पूर्णांकerrupts, each represented by <bits> bits. This assumes
 * that <bits> is a घातer of two.
 */
#घोषणा VGIC_ADDR_IRQ_MASK(bits) (((bits) * 1024 / 8) - 1)

/*
 * (addr & mask) gives us the _byte_ offset क्रम the INT ID.
 * We multiply this by 8 the get the _bit_ offset, then भागide this by
 * the number of bits to learn the actual INT ID.
 * But instead of a भागision (which requires a "long long div" implementation),
 * we shअगरt by the binary logarithm of <bits>.
 * This assumes that <bits> is a घातer of two.
 */
#घोषणा VGIC_ADDR_TO_INTID(addr, bits)  (((addr) & VGIC_ADDR_IRQ_MASK(bits)) * \
					8 >> ilog2(bits))

/*
 * Some VGIC रेजिस्टरs store per-IRQ inक्रमmation, with a dअगरferent number
 * of bits per IRQ. For those रेजिस्टरs this macro is used.
 * The _WITH_LENGTH version instantiates रेजिस्टरs with a fixed length
 * and is mutually exclusive with the _PER_IRQ version.
 */
#घोषणा REGISTER_DESC_WITH_BITS_PER_IRQ(off, rd, wr, ur, uw, bpi, acc)	\
	अणु								\
		.reg_offset = off,					\
		.bits_per_irq = bpi,					\
		.len = bpi * 1024 / 8,					\
		.access_flags = acc,					\
		.पढ़ो = rd,						\
		.ग_लिखो = wr,						\
		.uaccess_पढ़ो = ur,					\
		.uaccess_ग_लिखो = uw,					\
	पूर्ण

#घोषणा REGISTER_DESC_WITH_LENGTH(off, rd, wr, length, acc)		\
	अणु								\
		.reg_offset = off,					\
		.bits_per_irq = 0,					\
		.len = length,						\
		.access_flags = acc,					\
		.पढ़ो = rd,						\
		.ग_लिखो = wr,						\
	पूर्ण

#घोषणा REGISTER_DESC_WITH_LENGTH_UACCESS(off, rd, wr, urd, uwr, length, acc) \
	अणु								\
		.reg_offset = off,					\
		.bits_per_irq = 0,					\
		.len = length,						\
		.access_flags = acc,					\
		.पढ़ो = rd,						\
		.ग_लिखो = wr,						\
		.uaccess_पढ़ो = urd,					\
		.uaccess_ग_लिखो = uwr,					\
	पूर्ण

अचिन्हित दीर्घ vgic_data_mmio_bus_to_host(स्थिर व्योम *val, अचिन्हित पूर्णांक len);

व्योम vgic_data_host_to_mmio_bus(व्योम *buf, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ data);

अचिन्हित दीर्घ extract_bytes(u64 data, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक num);

u64 update_64bit_reg(u64 reg, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len,
		     अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_raz(काष्ठा kvm_vcpu *vcpu,
				 gpa_t addr, अचिन्हित पूर्णांक len);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_rao(काष्ठा kvm_vcpu *vcpu,
				 gpa_t addr, अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_wi(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val);

पूर्णांक vgic_mmio_uaccess_ग_लिखो_wi(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			       अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_group(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
				   अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_group(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			   अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_enable(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_senable(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val);

व्योम vgic_mmio_ग_लिखो_cenable(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val);

पूर्णांक vgic_uaccess_ग_लिखो_senable(काष्ठा kvm_vcpu *vcpu,
			       gpa_t addr, अचिन्हित पूर्णांक len,
			       अचिन्हित दीर्घ val);

पूर्णांक vgic_uaccess_ग_लिखो_cenable(काष्ठा kvm_vcpu *vcpu,
			       gpa_t addr, अचिन्हित पूर्णांक len,
			       अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_pending(काष्ठा kvm_vcpu *vcpu,
				     gpa_t addr, अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_spending(काष्ठा kvm_vcpu *vcpu,
			      gpa_t addr, अचिन्हित पूर्णांक len,
			      अचिन्हित दीर्घ val);

व्योम vgic_mmio_ग_लिखो_cpending(काष्ठा kvm_vcpu *vcpu,
			      gpa_t addr, अचिन्हित पूर्णांक len,
			      अचिन्हित दीर्घ val);

पूर्णांक vgic_uaccess_ग_लिखो_spending(काष्ठा kvm_vcpu *vcpu,
				gpa_t addr, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ val);

पूर्णांक vgic_uaccess_ग_लिखो_cpending(काष्ठा kvm_vcpu *vcpu,
				gpa_t addr, अचिन्हित पूर्णांक len,
				अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_active(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len);

अचिन्हित दीर्घ vgic_uaccess_पढ़ो_active(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_cactive(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val);

व्योम vgic_mmio_ग_लिखो_sactive(काष्ठा kvm_vcpu *vcpu,
			     gpa_t addr, अचिन्हित पूर्णांक len,
			     अचिन्हित दीर्घ val);

पूर्णांक vgic_mmio_uaccess_ग_लिखो_cactive(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len,
				    अचिन्हित दीर्घ val);

पूर्णांक vgic_mmio_uaccess_ग_लिखो_sactive(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len,
				    अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_priority(काष्ठा kvm_vcpu *vcpu,
				      gpa_t addr, अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_priority(काष्ठा kvm_vcpu *vcpu,
			      gpa_t addr, अचिन्हित पूर्णांक len,
			      अचिन्हित दीर्घ val);

अचिन्हित दीर्घ vgic_mmio_पढ़ो_config(काष्ठा kvm_vcpu *vcpu,
				    gpa_t addr, अचिन्हित पूर्णांक len);

व्योम vgic_mmio_ग_लिखो_config(काष्ठा kvm_vcpu *vcpu,
			    gpa_t addr, अचिन्हित पूर्णांक len,
			    अचिन्हित दीर्घ val);

पूर्णांक vgic_uaccess(काष्ठा kvm_vcpu *vcpu, काष्ठा vgic_io_device *dev,
		 bool is_ग_लिखो, पूर्णांक offset, u32 *val);

u64 vgic_पढ़ो_irq_line_level_info(काष्ठा kvm_vcpu *vcpu, u32 पूर्णांकid);

व्योम vgic_ग_लिखो_irq_line_level_info(काष्ठा kvm_vcpu *vcpu, u32 पूर्णांकid,
				    स्थिर u64 val);

अचिन्हित पूर्णांक vgic_v2_init_dist_iodev(काष्ठा vgic_io_device *dev);

अचिन्हित पूर्णांक vgic_v3_init_dist_iodev(काष्ठा vgic_io_device *dev);

u64 vgic_sanitise_outer_cacheability(u64 reg);
u64 vgic_sanitise_inner_cacheability(u64 reg);
u64 vgic_sanitise_shareability(u64 reg);
u64 vgic_sanitise_field(u64 reg, u64 field_mask, पूर्णांक field_shअगरt,
			u64 (*sanitise_fn)(u64));

/* Find the proper रेजिस्टर handler entry given a certain address offset */
स्थिर काष्ठा vgic_रेजिस्टर_region *
vgic_find_mmio_region(स्थिर काष्ठा vgic_रेजिस्टर_region *regions,
		      पूर्णांक nr_regions, अचिन्हित पूर्णांक offset);

#पूर्ण_अगर
