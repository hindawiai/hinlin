<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007, 2008, 2009, 2010, 2011 Cavium Networks
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/moduleparam.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-npei-defs.h>
#समावेश <यंत्र/octeon/cvmx-pciercx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pescx-defs.h>
#समावेश <यंत्र/octeon/cvmx-pexp-defs.h>
#समावेश <यंत्र/octeon/cvmx-pemx-defs.h>
#समावेश <यंत्र/octeon/cvmx-dpi-defs.h>
#समावेश <यंत्र/octeon/cvmx-sli-defs.h>
#समावेश <यंत्र/octeon/cvmx-sriox-defs.h>
#समावेश <यंत्र/octeon/cvmx-helper-errata.h>
#समावेश <यंत्र/octeon/pci-octeon.h>

#घोषणा MRRS_CN5XXX 0 /* 128 byte Max Read Request Size */
#घोषणा MPS_CN5XXX  0 /* 128 byte Max Packet Size (Limit of most PCs) */
#घोषणा MRRS_CN6XXX 3 /* 1024 byte Max Read Request Size */
#घोषणा MPS_CN6XXX  0 /* 128 byte Max Packet Size (Limit of most PCs) */

/* Module parameter to disable PCI probing */
अटल पूर्णांक pcie_disable;
module_param(pcie_disable, पूर्णांक, S_IRUGO);

अटल पूर्णांक enable_pcie_14459_war;
अटल पूर्णांक enable_pcie_bus_num_war[2];

जोड़ cvmx_pcie_address अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		uपूर्णांक64_t upper:2;	/* Normally 2 क्रम XKPHYS */
		uपूर्णांक64_t reserved_49_61:13;	/* Must be zero */
		uपूर्णांक64_t io:1;	/* 1 क्रम IO space access */
		uपूर्णांक64_t did:5; /* PCIe DID = 3 */
		uपूर्णांक64_t subdid:3;	/* PCIe SubDID = 1 */
		uपूर्णांक64_t reserved_36_39:4;	/* Must be zero */
		uपूर्णांक64_t es:2;	/* Endian swap = 1 */
		uपूर्णांक64_t port:2;	/* PCIe port 0,1 */
		uपूर्णांक64_t reserved_29_31:3;	/* Must be zero */
		/*
		 * Selects the type of the configuration request (0 = type 0,
		 * 1 = type 1).
		 */
		uपूर्णांक64_t ty:1;
		/* Target bus number sent in the ID in the request. */
		uपूर्णांक64_t bus:8;
		/*
		 * Target device number sent in the ID in the
		 * request. Note that Dev must be zero क्रम type 0
		 * configuration requests.
		 */
		uपूर्णांक64_t dev:5;
		/* Target function number sent in the ID in the request. */
		uपूर्णांक64_t func:3;
		/*
		 * Selects a रेजिस्टर in the configuration space of
		 * the target.
		 */
		uपूर्णांक64_t reg:12;
	पूर्ण config;
	काष्ठा अणु
		uपूर्णांक64_t upper:2;	/* Normally 2 क्रम XKPHYS */
		uपूर्णांक64_t reserved_49_61:13;	/* Must be zero */
		uपूर्णांक64_t io:1;	/* 1 क्रम IO space access */
		uपूर्णांक64_t did:5; /* PCIe DID = 3 */
		uपूर्णांक64_t subdid:3;	/* PCIe SubDID = 2 */
		uपूर्णांक64_t reserved_36_39:4;	/* Must be zero */
		uपूर्णांक64_t es:2;	/* Endian swap = 1 */
		uपूर्णांक64_t port:2;	/* PCIe port 0,1 */
		uपूर्णांक64_t address:32;	/* PCIe IO address */
	पूर्ण io;
	काष्ठा अणु
		uपूर्णांक64_t upper:2;	/* Normally 2 क्रम XKPHYS */
		uपूर्णांक64_t reserved_49_61:13;	/* Must be zero */
		uपूर्णांक64_t io:1;	/* 1 क्रम IO space access */
		uपूर्णांक64_t did:5; /* PCIe DID = 3 */
		uपूर्णांक64_t subdid:3;	/* PCIe SubDID = 3-6 */
		uपूर्णांक64_t reserved_36_39:4;	/* Must be zero */
		uपूर्णांक64_t address:36;	/* PCIe Mem address */
	पूर्ण mem;
पूर्ण;

अटल पूर्णांक cvmx_pcie_rc_initialize(पूर्णांक pcie_port);

/**
 * Return the Core भव base address क्रम PCIe IO access. IOs are
 * पढ़ो/written as an offset from this address.
 *
 * @pcie_port: PCIe port the IO is क्रम
 *
 * Returns 64bit Octeon IO base address क्रम पढ़ो/ग_लिखो
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_pcie_get_io_base_address(पूर्णांक pcie_port)
अणु
	जोड़ cvmx_pcie_address pcie_addr;
	pcie_addr.u64 = 0;
	pcie_addr.io.upper = 0;
	pcie_addr.io.io = 1;
	pcie_addr.io.did = 3;
	pcie_addr.io.subdid = 2;
	pcie_addr.io.es = 1;
	pcie_addr.io.port = pcie_port;
	वापस pcie_addr.u64;
पूर्ण

/**
 * Size of the IO address region वापसed at address
 * cvmx_pcie_get_io_base_address()
 *
 * @pcie_port: PCIe port the IO is क्रम
 *
 * Returns Size of the IO winकरोw
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_pcie_get_io_size(पूर्णांक pcie_port)
अणु
	वापस 1ull << 32;
पूर्ण

/**
 * Return the Core भव base address क्रम PCIe MEM access. Memory is
 * पढ़ो/written as an offset from this address.
 *
 * @pcie_port: PCIe port the IO is क्रम
 *
 * Returns 64bit Octeon IO base address क्रम पढ़ो/ग_लिखो
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_pcie_get_mem_base_address(पूर्णांक pcie_port)
अणु
	जोड़ cvmx_pcie_address pcie_addr;
	pcie_addr.u64 = 0;
	pcie_addr.mem.upper = 0;
	pcie_addr.mem.io = 1;
	pcie_addr.mem.did = 3;
	pcie_addr.mem.subdid = 3 + pcie_port;
	वापस pcie_addr.u64;
पूर्ण

/**
 * Size of the Mem address region वापसed at address
 * cvmx_pcie_get_mem_base_address()
 *
 * @pcie_port: PCIe port the IO is क्रम
 *
 * Returns Size of the Mem winकरोw
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_pcie_get_mem_size(पूर्णांक pcie_port)
अणु
	वापस 1ull << 36;
पूर्ण

/**
 * Read a PCIe config space रेजिस्टर indirectly. This is used क्रम
 * रेजिस्टरs of the क्रमm PCIEEP_CFG??? and PCIERC?_CFG???.
 *
 * @pcie_port:	PCIe port to पढ़ो from
 * @cfg_offset: Address to पढ़ो
 *
 * Returns Value पढ़ो
 */
अटल uपूर्णांक32_t cvmx_pcie_cfgx_पढ़ो(पूर्णांक pcie_port, uपूर्णांक32_t cfg_offset)
अणु
	अगर (octeon_has_feature(OCTEON_FEATURE_NPEI)) अणु
		जोड़ cvmx_pescx_cfg_rd pescx_cfg_rd;
		pescx_cfg_rd.u64 = 0;
		pescx_cfg_rd.s.addr = cfg_offset;
		cvmx_ग_लिखो_csr(CVMX_PESCX_CFG_RD(pcie_port), pescx_cfg_rd.u64);
		pescx_cfg_rd.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_CFG_RD(pcie_port));
		वापस pescx_cfg_rd.s.data;
	पूर्ण अन्यथा अणु
		जोड़ cvmx_pemx_cfg_rd pemx_cfg_rd;
		pemx_cfg_rd.u64 = 0;
		pemx_cfg_rd.s.addr = cfg_offset;
		cvmx_ग_लिखो_csr(CVMX_PEMX_CFG_RD(pcie_port), pemx_cfg_rd.u64);
		pemx_cfg_rd.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_CFG_RD(pcie_port));
		वापस pemx_cfg_rd.s.data;
	पूर्ण
पूर्ण

/**
 * Write a PCIe config space रेजिस्टर indirectly. This is used क्रम
 * रेजिस्टरs of the क्रमm PCIEEP_CFG??? and PCIERC?_CFG???.
 *
 * @pcie_port:	PCIe port to ग_लिखो to
 * @cfg_offset: Address to ग_लिखो
 * @val:	Value to ग_लिखो
 */
अटल व्योम cvmx_pcie_cfgx_ग_लिखो(पूर्णांक pcie_port, uपूर्णांक32_t cfg_offset,
				 uपूर्णांक32_t val)
अणु
	अगर (octeon_has_feature(OCTEON_FEATURE_NPEI)) अणु
		जोड़ cvmx_pescx_cfg_wr pescx_cfg_wr;
		pescx_cfg_wr.u64 = 0;
		pescx_cfg_wr.s.addr = cfg_offset;
		pescx_cfg_wr.s.data = val;
		cvmx_ग_लिखो_csr(CVMX_PESCX_CFG_WR(pcie_port), pescx_cfg_wr.u64);
	पूर्ण अन्यथा अणु
		जोड़ cvmx_pemx_cfg_wr pemx_cfg_wr;
		pemx_cfg_wr.u64 = 0;
		pemx_cfg_wr.s.addr = cfg_offset;
		pemx_cfg_wr.s.data = val;
		cvmx_ग_लिखो_csr(CVMX_PEMX_CFG_WR(pcie_port), pemx_cfg_wr.u64);
	पूर्ण
पूर्ण

/**
 * Build a PCIe config space request address क्रम a device
 *
 * @pcie_port: PCIe port to access
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 *
 * Returns 64bit Octeon IO address
 */
अटल अंतरभूत uपूर्णांक64_t __cvmx_pcie_build_config_addr(पूर्णांक pcie_port, पूर्णांक bus,
						     पूर्णांक dev, पूर्णांक fn, पूर्णांक reg)
अणु
	जोड़ cvmx_pcie_address pcie_addr;
	जोड़ cvmx_pciercx_cfg006 pciercx_cfg006;

	pciercx_cfg006.u32 =
	    cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG006(pcie_port));
	अगर ((bus <= pciercx_cfg006.s.pbnum) && (dev != 0))
		वापस 0;

	pcie_addr.u64 = 0;
	pcie_addr.config.upper = 2;
	pcie_addr.config.io = 1;
	pcie_addr.config.did = 3;
	pcie_addr.config.subdid = 1;
	pcie_addr.config.es = 1;
	pcie_addr.config.port = pcie_port;
	pcie_addr.config.ty = (bus > pciercx_cfg006.s.pbnum);
	pcie_addr.config.bus = bus;
	pcie_addr.config.dev = dev;
	pcie_addr.config.func = fn;
	pcie_addr.config.reg = reg;
	वापस pcie_addr.u64;
पूर्ण

/**
 * Read 8bits from a Device's config space
 *
 * @pcie_port: PCIe port the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 *
 * Returns Result of the पढ़ो
 */
अटल uपूर्णांक8_t cvmx_pcie_config_पढ़ो8(पूर्णांक pcie_port, पूर्णांक bus, पूर्णांक dev,
				      पूर्णांक fn, पूर्णांक reg)
अणु
	uपूर्णांक64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	अगर (address)
		वापस cvmx_पढ़ो64_uपूर्णांक8(address);
	अन्यथा
		वापस 0xff;
पूर्ण

/**
 * Read 16bits from a Device's config space
 *
 * @pcie_port: PCIe port the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 *
 * Returns Result of the पढ़ो
 */
अटल uपूर्णांक16_t cvmx_pcie_config_पढ़ो16(पूर्णांक pcie_port, पूर्णांक bus, पूर्णांक dev,
					पूर्णांक fn, पूर्णांक reg)
अणु
	uपूर्णांक64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	अगर (address)
		वापस le16_to_cpu(cvmx_पढ़ो64_uपूर्णांक16(address));
	अन्यथा
		वापस 0xffff;
पूर्ण

/**
 * Read 32bits from a Device's config space
 *
 * @pcie_port: PCIe port the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 *
 * Returns Result of the पढ़ो
 */
अटल uपूर्णांक32_t cvmx_pcie_config_पढ़ो32(पूर्णांक pcie_port, पूर्णांक bus, पूर्णांक dev,
					पूर्णांक fn, पूर्णांक reg)
अणु
	uपूर्णांक64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	अगर (address)
		वापस le32_to_cpu(cvmx_पढ़ो64_uपूर्णांक32(address));
	अन्यथा
		वापस 0xffffffff;
पूर्ण

/**
 * Write 8bits to a Device's config space
 *
 * @pcie_port: PCIe port the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 * @val:       Value to ग_लिखो
 */
अटल व्योम cvmx_pcie_config_ग_लिखो8(पूर्णांक pcie_port, पूर्णांक bus, पूर्णांक dev, पूर्णांक fn,
				    पूर्णांक reg, uपूर्णांक8_t val)
अणु
	uपूर्णांक64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	अगर (address)
		cvmx_ग_लिखो64_uपूर्णांक8(address, val);
पूर्ण

/**
 * Write 16bits to a Device's config space
 *
 * @pcie_port: PCIe port the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 * @val:       Value to ग_लिखो
 */
अटल व्योम cvmx_pcie_config_ग_लिखो16(पूर्णांक pcie_port, पूर्णांक bus, पूर्णांक dev, पूर्णांक fn,
				     पूर्णांक reg, uपूर्णांक16_t val)
अणु
	uपूर्णांक64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	अगर (address)
		cvmx_ग_लिखो64_uपूर्णांक16(address, cpu_to_le16(val));
पूर्ण

/**
 * Write 32bits to a Device's config space
 *
 * @pcie_port: PCIe port the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @reg:       Register to access
 * @val:       Value to ग_लिखो
 */
अटल व्योम cvmx_pcie_config_ग_लिखो32(पूर्णांक pcie_port, पूर्णांक bus, पूर्णांक dev, पूर्णांक fn,
				     पूर्णांक reg, uपूर्णांक32_t val)
अणु
	uपूर्णांक64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	अगर (address)
		cvmx_ग_लिखो64_uपूर्णांक32(address, cpu_to_le32(val));
पूर्ण

/**
 * Initialize the RC config space CSRs
 *
 * @pcie_port: PCIe port to initialize
 */
अटल व्योम __cvmx_pcie_rc_initialize_config_space(पूर्णांक pcie_port)
अणु
	जोड़ cvmx_pciercx_cfg030 pciercx_cfg030;
	जोड़ cvmx_pciercx_cfg070 pciercx_cfg070;
	जोड़ cvmx_pciercx_cfg001 pciercx_cfg001;
	जोड़ cvmx_pciercx_cfg032 pciercx_cfg032;
	जोड़ cvmx_pciercx_cfg006 pciercx_cfg006;
	जोड़ cvmx_pciercx_cfg008 pciercx_cfg008;
	जोड़ cvmx_pciercx_cfg009 pciercx_cfg009;
	जोड़ cvmx_pciercx_cfg010 pciercx_cfg010;
	जोड़ cvmx_pciercx_cfg011 pciercx_cfg011;
	जोड़ cvmx_pciercx_cfg035 pciercx_cfg035;
	जोड़ cvmx_pciercx_cfg075 pciercx_cfg075;
	जोड़ cvmx_pciercx_cfg034 pciercx_cfg034;

	/* Max Payload Size (PCIE*_CFG030[MPS]) */
	/* Max Read Request Size (PCIE*_CFG030[MRRS]) */
	/* Relaxed-order, no-snoop enables (PCIE*_CFG030[RO_EN,NS_EN] */
	/* Error Message Enables (PCIE*_CFG030[CE_EN,NFE_EN,FE_EN,UR_EN]) */

	pciercx_cfg030.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG030(pcie_port));
	अगर (OCTEON_IS_MODEL(OCTEON_CN5XXX)) अणु
		pciercx_cfg030.s.mps = MPS_CN5XXX;
		pciercx_cfg030.s.mrrs = MRRS_CN5XXX;
	पूर्ण अन्यथा अणु
		pciercx_cfg030.s.mps = MPS_CN6XXX;
		pciercx_cfg030.s.mrrs = MRRS_CN6XXX;
	पूर्ण
	/*
	 * Enable relaxed order processing. This will allow devices to
	 * affect पढ़ो response ordering.
	 */
	pciercx_cfg030.s.ro_en = 1;
	/* Enable no snoop processing. Not used by Octeon */
	pciercx_cfg030.s.ns_en = 1;
	/* Correctable error reporting enable. */
	pciercx_cfg030.s.ce_en = 1;
	/* Non-fatal error reporting enable. */
	pciercx_cfg030.s.nfe_en = 1;
	/* Fatal error reporting enable. */
	pciercx_cfg030.s.fe_en = 1;
	/* Unsupported request reporting enable. */
	pciercx_cfg030.s.ur_en = 1;
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG030(pcie_port), pciercx_cfg030.u32);


	अगर (octeon_has_feature(OCTEON_FEATURE_NPEI)) अणु
		जोड़ cvmx_npei_ctl_status2 npei_ctl_status2;
		/*
		 * Max Payload Size (NPEI_CTL_STATUS2[MPS]) must match
		 * PCIE*_CFG030[MPS].  Max Read Request Size
		 * (NPEI_CTL_STATUS2[MRRS]) must not exceed
		 * PCIE*_CFG030[MRRS]
		 */
		npei_ctl_status2.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_CTL_STATUS2);
		/* Max payload size = 128 bytes क्रम best Octeon DMA perक्रमmance */
		npei_ctl_status2.s.mps = MPS_CN5XXX;
		/* Max पढ़ो request size = 128 bytes क्रम best Octeon DMA perक्रमmance */
		npei_ctl_status2.s.mrrs = MRRS_CN5XXX;
		अगर (pcie_port)
			npei_ctl_status2.s.c1_b1_s = 3; /* Port1 BAR1 Size 256MB */
		अन्यथा
			npei_ctl_status2.s.c0_b1_s = 3; /* Port0 BAR1 Size 256MB */

		cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_CTL_STATUS2, npei_ctl_status2.u64);
	पूर्ण अन्यथा अणु
		/*
		 * Max Payload Size (DPI_SLI_PRTX_CFG[MPS]) must match
		 * PCIE*_CFG030[MPS].  Max Read Request Size
		 * (DPI_SLI_PRTX_CFG[MRRS]) must not exceed
		 * PCIE*_CFG030[MRRS].
		 */
		जोड़ cvmx_dpi_sli_prtx_cfg prt_cfg;
		जोड़ cvmx_sli_s2m_portx_ctl sli_s2m_portx_ctl;
		prt_cfg.u64 = cvmx_पढ़ो_csr(CVMX_DPI_SLI_PRTX_CFG(pcie_port));
		prt_cfg.s.mps = MPS_CN6XXX;
		prt_cfg.s.mrrs = MRRS_CN6XXX;
		/* Max outstanding load request. */
		prt_cfg.s.molr = 32;
		cvmx_ग_लिखो_csr(CVMX_DPI_SLI_PRTX_CFG(pcie_port), prt_cfg.u64);

		sli_s2m_portx_ctl.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_SLI_S2M_PORTX_CTL(pcie_port));
		sli_s2m_portx_ctl.s.mrrs = MRRS_CN6XXX;
		cvmx_ग_लिखो_csr(CVMX_PEXP_SLI_S2M_PORTX_CTL(pcie_port), sli_s2m_portx_ctl.u64);
	पूर्ण

	/* ECRC Generation (PCIE*_CFG070[GE,CE]) */
	pciercx_cfg070.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG070(pcie_port));
	pciercx_cfg070.s.ge = 1;	/* ECRC generation enable. */
	pciercx_cfg070.s.ce = 1;	/* ECRC check enable. */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG070(pcie_port), pciercx_cfg070.u32);

	/*
	 * Access Enables (PCIE*_CFG001[MSAE,ME])
	 * ME and MSAE should always be set.
	 * Interrupt Disable (PCIE*_CFG001[I_DIS])
	 * System Error Message Enable (PCIE*_CFG001[SEE])
	 */
	pciercx_cfg001.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG001(pcie_port));
	pciercx_cfg001.s.msae = 1;	/* Memory space enable. */
	pciercx_cfg001.s.me = 1;	/* Bus master enable. */
	pciercx_cfg001.s.i_dis = 1;	/* INTx निश्चितion disable. */
	pciercx_cfg001.s.see = 1;	/* SERR# enable */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG001(pcie_port), pciercx_cfg001.u32);

	/* Advanced Error Recovery Message Enables */
	/* (PCIE*_CFG066,PCIE*_CFG067,PCIE*_CFG069) */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG066(pcie_port), 0);
	/* Use CVMX_PCIERCX_CFG067 hardware शेष */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG069(pcie_port), 0);


	/* Active State Power Management (PCIE*_CFG032[ASLPC]) */
	pciercx_cfg032.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	pciercx_cfg032.s.aslpc = 0; /* Active state Link PM control. */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG032(pcie_port), pciercx_cfg032.u32);

	/*
	 * Link Width Mode (PCIERCn_CFG452[LME]) - Set during
	 * cvmx_pcie_rc_initialize_link()
	 *
	 * Primary Bus Number (PCIERCn_CFG006[PBNUM])
	 *
	 * We set the primary bus number to 1 so IDT bridges are
	 * happy. They करोn't like zero.
	 */
	pciercx_cfg006.u32 = 0;
	pciercx_cfg006.s.pbnum = 1;
	pciercx_cfg006.s.sbnum = 1;
	pciercx_cfg006.s.subbnum = 1;
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG006(pcie_port), pciercx_cfg006.u32);


	/*
	 * Memory-mapped I/O BAR (PCIERCn_CFG008)
	 * Most applications should disable the memory-mapped I/O BAR by
	 * setting PCIERCn_CFG008[ML_ADDR] < PCIERCn_CFG008[MB_ADDR]
	 */
	pciercx_cfg008.u32 = 0;
	pciercx_cfg008.s.mb_addr = 0x100;
	pciercx_cfg008.s.ml_addr = 0;
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG008(pcie_port), pciercx_cfg008.u32);


	/*
	 * Prefetchable BAR (PCIERCn_CFG009,PCIERCn_CFG010,PCIERCn_CFG011)
	 * Most applications should disable the prefetchable BAR by setting
	 * PCIERCn_CFG011[UMEM_LIMIT],PCIERCn_CFG009[LMEM_LIMIT] <
	 * PCIERCn_CFG010[UMEM_BASE],PCIERCn_CFG009[LMEM_BASE]
	 */
	pciercx_cfg009.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG009(pcie_port));
	pciercx_cfg010.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG010(pcie_port));
	pciercx_cfg011.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG011(pcie_port));
	pciercx_cfg009.s.lmem_base = 0x100;
	pciercx_cfg009.s.lmem_limit = 0;
	pciercx_cfg010.s.umem_base = 0x100;
	pciercx_cfg011.s.umem_limit = 0;
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG009(pcie_port), pciercx_cfg009.u32);
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG010(pcie_port), pciercx_cfg010.u32);
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG011(pcie_port), pciercx_cfg011.u32);

	/*
	 * System Error Interrupt Enables (PCIERCn_CFG035[SECEE,SEFEE,SENFEE])
	 * PME Interrupt Enables (PCIERCn_CFG035[PMEIE])
	*/
	pciercx_cfg035.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG035(pcie_port));
	pciercx_cfg035.s.secee = 1; /* System error on correctable error enable. */
	pciercx_cfg035.s.sefee = 1; /* System error on fatal error enable. */
	pciercx_cfg035.s.senfee = 1; /* System error on non-fatal error enable. */
	pciercx_cfg035.s.pmeie = 1; /* PME पूर्णांकerrupt enable. */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG035(pcie_port), pciercx_cfg035.u32);

	/*
	 * Advanced Error Recovery Interrupt Enables
	 * (PCIERCn_CFG075[CERE,NFERE,FERE])
	 */
	pciercx_cfg075.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG075(pcie_port));
	pciercx_cfg075.s.cere = 1; /* Correctable error reporting enable. */
	pciercx_cfg075.s.nfere = 1; /* Non-fatal error reporting enable. */
	pciercx_cfg075.s.fere = 1; /* Fatal error reporting enable. */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG075(pcie_port), pciercx_cfg075.u32);

	/*
	 * HP Interrupt Enables (PCIERCn_CFG034[HPINT_EN],
	 * PCIERCn_CFG034[DLLS_EN,CCINT_EN])
	 */
	pciercx_cfg034.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG034(pcie_port));
	pciercx_cfg034.s.hpपूर्णांक_en = 1; /* Hot-plug पूर्णांकerrupt enable. */
	pciercx_cfg034.s.dlls_en = 1; /* Data Link Layer state changed enable */
	pciercx_cfg034.s.ccपूर्णांक_en = 1; /* Command completed पूर्णांकerrupt enable. */
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG034(pcie_port), pciercx_cfg034.u32);
पूर्ण

/**
 * Initialize a host mode PCIe gen 1 link. This function takes a PCIe
 * port from reset to a link up state. Software can then begin
 * configuring the rest of the link.
 *
 * @pcie_port: PCIe port to initialize
 *
 * Returns Zero on success
 */
अटल पूर्णांक __cvmx_pcie_rc_initialize_link_gen1(पूर्णांक pcie_port)
अणु
	uपूर्णांक64_t start_cycle;
	जोड़ cvmx_pescx_ctl_status pescx_ctl_status;
	जोड़ cvmx_pciercx_cfg452 pciercx_cfg452;
	जोड़ cvmx_pciercx_cfg032 pciercx_cfg032;
	जोड़ cvmx_pciercx_cfg448 pciercx_cfg448;

	/* Set the lane width */
	pciercx_cfg452.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG452(pcie_port));
	pescx_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_CTL_STATUS(pcie_port));
	अगर (pescx_ctl_status.s.qlm_cfg == 0)
		/* We're in 8 lane (56XX) or 4 lane (54XX) mode */
		pciercx_cfg452.s.lme = 0xf;
	अन्यथा
		/* We're in 4 lane (56XX) or 2 lane (52XX) mode */
		pciercx_cfg452.s.lme = 0x7;
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG452(pcie_port), pciercx_cfg452.u32);

	/*
	 * CN52XX pass 1.x has an errata where length mismatches on UR
	 * responses can cause bus errors on 64bit memory
	 * पढ़ोs. Turning off length error checking fixes this.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) अणु
		जोड़ cvmx_pciercx_cfg455 pciercx_cfg455;
		pciercx_cfg455.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG455(pcie_port));
		pciercx_cfg455.s.m_cpl_len_err = 1;
		cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG455(pcie_port), pciercx_cfg455.u32);
	पूर्ण

	/* Lane swap needs to be manually enabled क्रम CN52XX */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX) && (pcie_port == 1)) अणु
		pescx_ctl_status.s.lane_swp = 1;
		cvmx_ग_लिखो_csr(CVMX_PESCX_CTL_STATUS(pcie_port), pescx_ctl_status.u64);
	पूर्ण

	/* Bring up the link */
	pescx_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_CTL_STATUS(pcie_port));
	pescx_ctl_status.s.lnk_enb = 1;
	cvmx_ग_लिखो_csr(CVMX_PESCX_CTL_STATUS(pcie_port), pescx_ctl_status.u64);

	/*
	 * CN52XX pass 1.0: Due to a bug in 2nd order CDR, it needs to
	 * be disabled.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_0))
		__cvmx_helper_errata_qlm_disable_2nd_order_cdr(0);

	/* Wait क्रम the link to come up */
	start_cycle = cvmx_get_cycle();
	करो अणु
		अगर (cvmx_get_cycle() - start_cycle > 2 * octeon_get_घड़ी_rate()) अणु
			cvmx_dम_लिखो("PCIe: Port %d link timeout\n", pcie_port);
			वापस -1;
		पूर्ण
		__delay(10000);
		pciercx_cfg032.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	पूर्ण जबतक (pciercx_cfg032.s.dlla == 0);

	/* Clear all pending errors */
	cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_INT_SUM, cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_INT_SUM));

	/*
	 * Update the Replay Time Limit. Empirically, some PCIe
	 * devices take a little दीर्घer to respond than expected under
	 * load. As a workaround क्रम this we configure the Replay Time
	 * Limit to the value expected क्रम a 512 byte MPS instead of
	 * our actual 256 byte MPS. The numbers below are directly
	 * from the PCIe spec table 3-4.
	 */
	pciercx_cfg448.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG448(pcie_port));
	चयन (pciercx_cfg032.s.nlw) अणु
	हाल 1:		/* 1 lane */
		pciercx_cfg448.s.rtl = 1677;
		अवरोध;
	हाल 2:		/* 2 lanes */
		pciercx_cfg448.s.rtl = 867;
		अवरोध;
	हाल 4:		/* 4 lanes */
		pciercx_cfg448.s.rtl = 462;
		अवरोध;
	हाल 8:		/* 8 lanes */
		pciercx_cfg448.s.rtl = 258;
		अवरोध;
	पूर्ण
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG448(pcie_port), pciercx_cfg448.u32);

	वापस 0;
पूर्ण

अटल व्योम __cvmx_increment_ba(जोड़ cvmx_sli_mem_access_subidx *pmas)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		pmas->cn68xx.ba++;
	अन्यथा
		pmas->s.ba++;
पूर्ण

/**
 * Initialize a PCIe gen 1 port क्रम use in host(RC) mode. It करोesn't
 * क्रमागतerate the bus.
 *
 * @pcie_port: PCIe port to initialize
 *
 * Returns Zero on success
 */
अटल पूर्णांक __cvmx_pcie_rc_initialize_gen1(पूर्णांक pcie_port)
अणु
	पूर्णांक i;
	पूर्णांक base;
	u64 addr_swizzle;
	जोड़ cvmx_ciu_soft_prst ciu_soft_prst;
	जोड़ cvmx_pescx_bist_status pescx_bist_status;
	जोड़ cvmx_pescx_bist_status2 pescx_bist_status2;
	जोड़ cvmx_npei_ctl_status npei_ctl_status;
	जोड़ cvmx_npei_mem_access_ctl npei_mem_access_ctl;
	जोड़ cvmx_npei_mem_access_subidx mem_access_subid;
	जोड़ cvmx_npei_dbg_data npei_dbg_data;
	जोड़ cvmx_pescx_ctl_status2 pescx_ctl_status2;
	जोड़ cvmx_pciercx_cfg032 pciercx_cfg032;
	जोड़ cvmx_npei_bar1_indexx bar1_index;

retry:
	/*
	 * Make sure we aren't trying to setup a target mode पूर्णांकerface
	 * in host mode.
	 */
	npei_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_CTL_STATUS);
	अगर ((pcie_port == 0) && !npei_ctl_status.s.host_mode) अणु
		cvmx_dम_लिखो("PCIe: Port %d in endpoint mode\n", pcie_port);
		वापस -1;
	पूर्ण

	/*
	 * Make sure a CN52XX isn't trying to bring up port 1 when it
	 * is disabled.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
		npei_dbg_data.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_DATA);
		अगर ((pcie_port == 1) && npei_dbg_data.cn52xx.qlm0_link_width) अणु
			cvmx_dम_लिखो("PCIe: ERROR: cvmx_pcie_rc_initialize() called on port1, but port1 is disabled\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/*
	 * PCIe चयन arbitration mode. '0' == fixed priority NPEI,
	 * PCIe0, then PCIe1. '1' == round robin.
	 */
	npei_ctl_status.s.arb = 1;
	/* Allow up to 0x20 config retries */
	npei_ctl_status.s.cfg_rtry = 0x20;
	/*
	 * CN52XX pass1.x has an errata where P0_NTAGS and P1_NTAGS
	 * करोn't reset.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) अणु
		npei_ctl_status.s.p0_ntags = 0x20;
		npei_ctl_status.s.p1_ntags = 0x20;
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_CTL_STATUS, npei_ctl_status.u64);

	/* Bring the PCIe out of reset */
	अगर (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_EBH5200) अणु
		/*
		 * The EBH5200 board swapped the PCIe reset lines on
		 * the board. As a workaround क्रम this bug, we bring
		 * both PCIe ports out of reset at the same समय
		 * instead of on separate calls. So क्रम port 0, we
		 * bring both out of reset and करो nothing on port 1
		 */
		अगर (pcie_port == 0) अणु
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST);
			/*
			 * After a chip reset the PCIe will also be in
			 * reset. If it isn't, most likely someone is
			 * trying to init it again without a proper
			 * PCIe reset.
			 */
			अगर (ciu_soft_prst.s.soft_prst == 0) अणु
				/* Reset the ports */
				ciu_soft_prst.s.soft_prst = 1;
				cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST, ciu_soft_prst.u64);
				ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST1);
				ciu_soft_prst.s.soft_prst = 1;
				cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST1, ciu_soft_prst.u64);
				/* Wait until pcie resets the ports. */
				udelay(2000);
			पूर्ण
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST1);
			ciu_soft_prst.s.soft_prst = 0;
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST1, ciu_soft_prst.u64);
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST);
			ciu_soft_prst.s.soft_prst = 0;
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST, ciu_soft_prst.u64);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The normal हाल: The PCIe ports are completely
		 * separate and can be brought out of reset
		 * independently.
		 */
		अगर (pcie_port)
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST1);
		अन्यथा
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST);
		/*
		 * After a chip reset the PCIe will also be in
		 * reset. If it isn't, most likely someone is trying
		 * to init it again without a proper PCIe reset.
		 */
		अगर (ciu_soft_prst.s.soft_prst == 0) अणु
			/* Reset the port */
			ciu_soft_prst.s.soft_prst = 1;
			अगर (pcie_port)
				cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST1, ciu_soft_prst.u64);
			अन्यथा
				cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST, ciu_soft_prst.u64);
			/* Wait until pcie resets the ports. */
			udelay(2000);
		पूर्ण
		अगर (pcie_port) अणु
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST1);
			ciu_soft_prst.s.soft_prst = 0;
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST1, ciu_soft_prst.u64);
		पूर्ण अन्यथा अणु
			ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST);
			ciu_soft_prst.s.soft_prst = 0;
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST, ciu_soft_prst.u64);
		पूर्ण
	पूर्ण

	/*
	 * Wait क्रम PCIe reset to complete. Due to errata PCIE-700, we
	 * करोn't poll PESCX_CTL_STATUS2[PCIERST], but simply रुको a
	 * fixed number of cycles.
	 */
	__delay(400000);

	/*
	 * PESCX_BIST_STATUS2[PCLK_RUN] was missing on pass 1 of
	 * CN56XX and CN52XX, so we only probe it on newer chips
	 */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X) && !OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) अणु
		/* Clear PCLK_RUN so we can check अगर the घड़ी is running */
		pescx_ctl_status2.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_CTL_STATUS2(pcie_port));
		pescx_ctl_status2.s.pclk_run = 1;
		cvmx_ग_लिखो_csr(CVMX_PESCX_CTL_STATUS2(pcie_port), pescx_ctl_status2.u64);
		/* Now that we cleared PCLK_RUN, रुको क्रम it to be set
		 * again telling us the घड़ी is running
		 */
		अगर (CVMX_WAIT_FOR_FIELD64(CVMX_PESCX_CTL_STATUS2(pcie_port),
					  जोड़ cvmx_pescx_ctl_status2, pclk_run, ==, 1, 10000)) अणु
			cvmx_dम_लिखो("PCIe: Port %d isn't clocked, skipping.\n", pcie_port);
			वापस -1;
		पूर्ण
	पूर्ण

	/*
	 * Check and make sure PCIe came out of reset. If it करोesn't
	 * the board probably hasn't wired the घड़ीs up and the
	 * पूर्णांकerface should be skipped.
	 */
	pescx_ctl_status2.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_CTL_STATUS2(pcie_port));
	अगर (pescx_ctl_status2.s.pcierst) अणु
		cvmx_dम_लिखो("PCIe: Port %d stuck in reset, skipping.\n", pcie_port);
		वापस -1;
	पूर्ण

	/*
	 * Check BIST2 status. If any bits are set skip this
	 * पूर्णांकerface. This is an attempt to catch PCIE-813 on pass 1
	 * parts.
	 */
	pescx_bist_status2.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_BIST_STATUS2(pcie_port));
	अगर (pescx_bist_status2.u64) अणु
		cvmx_dम_लिखो("PCIe: Port %d BIST2 failed. Most likely this port isn't hooked up, skipping.\n",
			     pcie_port);
		वापस -1;
	पूर्ण

	/* Check BIST status */
	pescx_bist_status.u64 = cvmx_पढ़ो_csr(CVMX_PESCX_BIST_STATUS(pcie_port));
	अगर (pescx_bist_status.u64)
		cvmx_dम_लिखो("PCIe: BIST FAILED for port %d (0x%016llx)\n",
			     pcie_port, CAST64(pescx_bist_status.u64));

	/* Initialize the config space CSRs */
	__cvmx_pcie_rc_initialize_config_space(pcie_port);

	/* Bring the link up */
	अगर (__cvmx_pcie_rc_initialize_link_gen1(pcie_port)) अणु
		cvmx_dम_लिखो("PCIe: Failed to initialize port %d, probably the slot is empty\n",
			     pcie_port);
		वापस -1;
	पूर्ण

	/* Store merge control (NPEI_MEM_ACCESS_CTL[TIMER,MAX_WORD]) */
	npei_mem_access_ctl.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_MEM_ACCESS_CTL);
	npei_mem_access_ctl.s.max_word = 0;	/* Allow 16 words to combine */
	npei_mem_access_ctl.s.समयr = 127;	/* Wait up to 127 cycles क्रम more data */
	cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_MEM_ACCESS_CTL, npei_mem_access_ctl.u64);

	/* Setup Mem access SubDIDs */
	mem_access_subid.u64 = 0;
	mem_access_subid.s.port = pcie_port; /* Port the request is sent to. */
	mem_access_subid.s.nmerge = 1;	/* Due to an errata on pass 1 chips, no merging is allowed. */
	mem_access_subid.s.esr = 1;	/* Endian-swap क्रम Reads. */
	mem_access_subid.s.esw = 1;	/* Endian-swap क्रम Writes. */
	mem_access_subid.s.nsr = 0;	/* Enable Snooping क्रम Reads. Octeon करोesn't care, but devices might want this more conservative setting */
	mem_access_subid.s.nsw = 0;	/* Enable Snoop क्रम Writes. */
	mem_access_subid.s.ror = 0;	/* Disable Relaxed Ordering क्रम Reads. */
	mem_access_subid.s.row = 0;	/* Disable Relaxed Ordering क्रम Writes. */
	mem_access_subid.s.ba = 0;	/* PCIe Adddress Bits <63:34>. */

	/*
	 * Setup mem access 12-15 क्रम port 0, 16-19 क्रम port 1,
	 * supplying 36 bits of address space.
	 */
	क्रम (i = 12 + pcie_port * 4; i < 16 + pcie_port * 4; i++) अणु
		cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_MEM_ACCESS_SUBIDX(i), mem_access_subid.u64);
		mem_access_subid.s.ba += 1; /* Set each SUBID to extend the addressable range */
	पूर्ण

	/*
	 * Disable the peer to peer क्रमwarding रेजिस्टर. This must be
	 * setup by the OS after it क्रमागतerates the bus and assigns
	 * addresses to the PCIe busses.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		cvmx_ग_लिखो_csr(CVMX_PESCX_P2P_BARX_START(i, pcie_port), -1);
		cvmx_ग_लिखो_csr(CVMX_PESCX_P2P_BARX_END(i, pcie_port), -1);
	पूर्ण

	/* Set Octeon's BAR0 to decode 0-16KB. It overlaps with Bar2 */
	cvmx_ग_लिखो_csr(CVMX_PESCX_P2N_BAR0_START(pcie_port), 0);

	/* BAR1 follows BAR2 with a gap so it has the same address as क्रम gen2. */
	cvmx_ग_लिखो_csr(CVMX_PESCX_P2N_BAR1_START(pcie_port), CVMX_PCIE_BAR1_RC_BASE);

	bar1_index.u32 = 0;
	bar1_index.s.addr_idx = (CVMX_PCIE_BAR1_PHYS_BASE >> 22);
	bar1_index.s.ca = 1;	   /* Not Cached */
	bar1_index.s.end_swp = 1;  /* Endian Swap mode */
	bar1_index.s.addr_v = 1;   /* Valid entry */

	base = pcie_port ? 16 : 0;

	/* Big endian swizzle क्रम 32-bit PEXP_NCB रेजिस्टर. */
#अगर_घोषित __MIPSEB__
	addr_swizzle = 4;
#अन्यथा
	addr_swizzle = 0;
#पूर्ण_अगर
	क्रम (i = 0; i < 16; i++) अणु
		cvmx_ग_लिखो64_uपूर्णांक32((CVMX_PEXP_NPEI_BAR1_INDEXX(base) ^ addr_swizzle),
				    bar1_index.u32);
		base++;
		/* 256MB / 16 >> 22 == 4 */
		bar1_index.s.addr_idx += (((1ull << 28) / 16ull) >> 22);
	पूर्ण

	/*
	 * Set Octeon's BAR2 to decode 0-2^39. Bar0 and Bar1 take
	 * precedence where they overlap. It also overlaps with the
	 * device addresses, so make sure the peer to peer क्रमwarding
	 * is set right.
	 */
	cvmx_ग_लिखो_csr(CVMX_PESCX_P2N_BAR2_START(pcie_port), 0);

	/*
	 * Setup BAR2 attributes
	 *
	 * Relaxed Ordering (NPEI_CTL_PORTn[PTLP_RO,CTLP_RO, WAIT_COM])
	 * - PTLP_RO,CTLP_RO should normally be set (except क्रम debug).
	 * - WAIT_COM=0 will likely work क्रम all applications.
	 *
	 * Load completion relaxed ordering (NPEI_CTL_PORTn[WAITL_COM]).
	 */
	अगर (pcie_port) अणु
		जोड़ cvmx_npei_ctl_port1 npei_ctl_port;
		npei_ctl_port.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_CTL_PORT1);
		npei_ctl_port.s.bar2_enb = 1;
		npei_ctl_port.s.bar2_esx = 1;
		npei_ctl_port.s.bar2_cax = 0;
		npei_ctl_port.s.ptlp_ro = 1;
		npei_ctl_port.s.ctlp_ro = 1;
		npei_ctl_port.s.रुको_com = 0;
		npei_ctl_port.s.रुकोl_com = 0;
		cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_CTL_PORT1, npei_ctl_port.u64);
	पूर्ण अन्यथा अणु
		जोड़ cvmx_npei_ctl_port0 npei_ctl_port;
		npei_ctl_port.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_CTL_PORT0);
		npei_ctl_port.s.bar2_enb = 1;
		npei_ctl_port.s.bar2_esx = 1;
		npei_ctl_port.s.bar2_cax = 0;
		npei_ctl_port.s.ptlp_ro = 1;
		npei_ctl_port.s.ctlp_ro = 1;
		npei_ctl_port.s.रुको_com = 0;
		npei_ctl_port.s.रुकोl_com = 0;
		cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_CTL_PORT0, npei_ctl_port.u64);
	पूर्ण

	/*
	 * Both pass 1 and pass 2 of CN52XX and CN56XX have an errata
	 * that causes TLP ordering to not be preserved after multiple
	 * PCIe port resets. This code detects this fault and corrects
	 * it by aligning the TLP counters properly. Another link
	 * reset is then perक्रमmed. See PCIE-13340
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS2_X) ||
	    OCTEON_IS_MODEL(OCTEON_CN52XX_PASS2_X) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X) ||
	    OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X)) अणु
		जोड़ cvmx_npei_dbg_data dbg_data;
		पूर्णांक old_in_fअगर_p_count;
		पूर्णांक in_fअगर_p_count;
		पूर्णांक out_p_count;
		पूर्णांक in_p_offset = (OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_X) || OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X)) ? 4 : 1;
		पूर्णांक i;

		/*
		 * Choose a ग_लिखो address of 1MB. It should be
		 * harmless as all bars haven't been setup.
		 */
		uपूर्णांक64_t ग_लिखो_address = (cvmx_pcie_get_mem_base_address(pcie_port) + 0x100000) | (1ull<<63);

		/*
		 * Make sure at least in_p_offset have been executed beक्रमe we try and
		 * पढ़ो in_fअगर_p_count
		 */
		i = in_p_offset;
		जबतक (i--) अणु
			cvmx_ग_लिखो64_uपूर्णांक32(ग_लिखो_address, 0);
			__delay(10000);
		पूर्ण

		/*
		 * Read the IN_FIF_P_COUNT from the debug
		 * select. IN_FIF_P_COUNT can be unstable someबार so
		 * पढ़ो it twice with a ग_लिखो between the पढ़ोs.  This
		 * way we can tell the value is good as it will
		 * increment by one due to the ग_लिखो
		 */
		cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_DBG_SELECT, (pcie_port) ? 0xd7fc : 0xcffc);
		cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_SELECT);
		करो अणु
			dbg_data.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_DATA);
			old_in_fअगर_p_count = dbg_data.s.data & 0xff;
			cvmx_ग_लिखो64_uपूर्णांक32(ग_लिखो_address, 0);
			__delay(10000);
			dbg_data.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_DATA);
			in_fअगर_p_count = dbg_data.s.data & 0xff;
		पूर्ण जबतक (in_fअगर_p_count != ((old_in_fअगर_p_count+1) & 0xff));

		/* Update in_fअगर_p_count क्रम it's offset with respect to out_p_count */
		in_fअगर_p_count = (in_fअगर_p_count + in_p_offset) & 0xff;

		/* Read the OUT_P_COUNT from the debug select */
		cvmx_ग_लिखो_csr(CVMX_PEXP_NPEI_DBG_SELECT, (pcie_port) ? 0xd00f : 0xc80f);
		cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_SELECT);
		dbg_data.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_DATA);
		out_p_count = (dbg_data.s.data>>1) & 0xff;

		/* Check that the two counters are aligned */
		अगर (out_p_count != in_fअगर_p_count) अणु
			cvmx_dम_लिखो("PCIe: Port %d aligning TLP counters as workaround to maintain ordering\n", pcie_port);
			जबतक (in_fअगर_p_count != 0) अणु
				cvmx_ग_लिखो64_uपूर्णांक32(ग_लिखो_address, 0);
				__delay(10000);
				in_fअगर_p_count = (in_fअगर_p_count + 1) & 0xff;
			पूर्ण
			/*
			 * The EBH5200 board swapped the PCIe reset
			 * lines on the board. This means we must
			 * bring both links करोwn and up, which will
			 * cause the PCIe0 to need alignment
			 * again. Lots of messages will be displayed,
			 * but everything should work
			 */
			अगर ((cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_EBH5200) &&
				(pcie_port == 1))
				cvmx_pcie_rc_initialize(0);
			/* Rety bringing this port up */
			जाओ retry;
		पूर्ण
	पूर्ण

	/* Display the link status */
	pciercx_cfg032.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	cvmx_dम_लिखो("PCIe: Port %d link active, %d lanes\n", pcie_port, pciercx_cfg032.s.nlw);

	वापस 0;
पूर्ण

/**
  * Initialize a host mode PCIe gen 2 link. This function takes a PCIe
 * port from reset to a link up state. Software can then begin
 * configuring the rest of the link.
 *
 * @pcie_port: PCIe port to initialize
 *
 * Return Zero on success.
 */
अटल पूर्णांक __cvmx_pcie_rc_initialize_link_gen2(पूर्णांक pcie_port)
अणु
	uपूर्णांक64_t start_cycle;
	जोड़ cvmx_pemx_ctl_status pem_ctl_status;
	जोड़ cvmx_pciercx_cfg032 pciercx_cfg032;
	जोड़ cvmx_pciercx_cfg448 pciercx_cfg448;

	/* Bring up the link */
	pem_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_CTL_STATUS(pcie_port));
	pem_ctl_status.s.lnk_enb = 1;
	cvmx_ग_लिखो_csr(CVMX_PEMX_CTL_STATUS(pcie_port), pem_ctl_status.u64);

	/* Wait क्रम the link to come up */
	start_cycle = cvmx_get_cycle();
	करो अणु
		अगर (cvmx_get_cycle() - start_cycle >  octeon_get_घड़ी_rate())
			वापस -1;
		__delay(10000);
		pciercx_cfg032.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	पूर्ण जबतक ((pciercx_cfg032.s.dlla == 0) || (pciercx_cfg032.s.lt == 1));

	/*
	 * Update the Replay Time Limit. Empirically, some PCIe
	 * devices take a little दीर्घer to respond than expected under
	 * load. As a workaround क्रम this we configure the Replay Time
	 * Limit to the value expected क्रम a 512 byte MPS instead of
	 * our actual 256 byte MPS. The numbers below are directly
	 * from the PCIe spec table 3-4
	 */
	pciercx_cfg448.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG448(pcie_port));
	चयन (pciercx_cfg032.s.nlw) अणु
	हाल 1: /* 1 lane */
		pciercx_cfg448.s.rtl = 1677;
		अवरोध;
	हाल 2: /* 2 lanes */
		pciercx_cfg448.s.rtl = 867;
		अवरोध;
	हाल 4: /* 4 lanes */
		pciercx_cfg448.s.rtl = 462;
		अवरोध;
	हाल 8: /* 8 lanes */
		pciercx_cfg448.s.rtl = 258;
		अवरोध;
	पूर्ण
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG448(pcie_port), pciercx_cfg448.u32);

	वापस 0;
पूर्ण


/**
 * Initialize a PCIe gen 2 port क्रम use in host(RC) mode. It करोesn't क्रमागतerate
 * the bus.
 *
 * @pcie_port: PCIe port to initialize
 *
 * Returns Zero on success.
 */
अटल पूर्णांक __cvmx_pcie_rc_initialize_gen2(पूर्णांक pcie_port)
अणु
	पूर्णांक i;
	जोड़ cvmx_ciu_soft_prst ciu_soft_prst;
	जोड़ cvmx_mio_rst_ctlx mio_rst_ctl;
	जोड़ cvmx_pemx_bar_ctl pemx_bar_ctl;
	जोड़ cvmx_pemx_ctl_status pemx_ctl_status;
	जोड़ cvmx_pemx_bist_status pemx_bist_status;
	जोड़ cvmx_pemx_bist_status2 pemx_bist_status2;
	जोड़ cvmx_pciercx_cfg032 pciercx_cfg032;
	जोड़ cvmx_pciercx_cfg515 pciercx_cfg515;
	जोड़ cvmx_sli_ctl_portx sli_ctl_portx;
	जोड़ cvmx_sli_mem_access_ctl sli_mem_access_ctl;
	जोड़ cvmx_sli_mem_access_subidx mem_access_subid;
	जोड़ cvmx_sriox_status_reg sriox_status_reg;
	जोड़ cvmx_pemx_bar1_indexx bar1_index;

	अगर (octeon_has_feature(OCTEON_FEATURE_SRIO)) अणु
		/* Make sure this पूर्णांकerface isn't SRIO */
		अगर (OCTEON_IS_MODEL(OCTEON_CN66XX)) अणु
			/*
			 * The CN66XX requires पढ़ोing the
			 * MIO_QLMX_CFG रेजिस्टर to figure out the
			 * port type.
			 */
			जोड़ cvmx_mio_qlmx_cfg qlmx_cfg;
			qlmx_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_QLMX_CFG(pcie_port));

			अगर (qlmx_cfg.s.qlm_spd == 15) अणु
				pr_notice("PCIe: Port %d is disabled, skipping.\n", pcie_port);
				वापस -1;
			पूर्ण

			चयन (qlmx_cfg.s.qlm_spd) अणु
			हाल 0x1: /* SRIO 1x4 लघु */
			हाल 0x3: /* SRIO 1x4 दीर्घ */
			हाल 0x4: /* SRIO 2x2 लघु */
			हाल 0x6: /* SRIO 2x2 दीर्घ */
				pr_notice("PCIe: Port %d is SRIO, skipping.\n", pcie_port);
				वापस -1;
			हाल 0x9: /* SGMII */
				pr_notice("PCIe: Port %d is SGMII, skipping.\n", pcie_port);
				वापस -1;
			हाल 0xb: /* XAUI */
				pr_notice("PCIe: Port %d is XAUI, skipping.\n", pcie_port);
				वापस -1;
			हाल 0x0: /* PCIE gen2 */
			हाल 0x8: /* PCIE gen2 (alias) */
			हाल 0x2: /* PCIE gen1 */
			हाल 0xa: /* PCIE gen1 (alias) */
				अवरोध;
			शेष:
				pr_notice("PCIe: Port %d is unknown, skipping.\n", pcie_port);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			sriox_status_reg.u64 = cvmx_पढ़ो_csr(CVMX_SRIOX_STATUS_REG(pcie_port));
			अगर (sriox_status_reg.s.srio) अणु
				pr_notice("PCIe: Port %d is SRIO, skipping.\n", pcie_port);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

#अगर 0
    /* This code is so that the PCIe analyzer is able to see 63XX traffic */
	pr_notice("PCIE : init for pcie analyzer.\n");
	cvmx_helper_qlm_jtag_init();
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 85);
	cvmx_helper_qlm_jtag_shअगरt(pcie_port, 1, 1);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 300-86);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 85);
	cvmx_helper_qlm_jtag_shअगरt(pcie_port, 1, 1);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 300-86);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 85);
	cvmx_helper_qlm_jtag_shअगरt(pcie_port, 1, 1);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 300-86);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 85);
	cvmx_helper_qlm_jtag_shअगरt(pcie_port, 1, 1);
	cvmx_helper_qlm_jtag_shअगरt_zeros(pcie_port, 300-86);
	cvmx_helper_qlm_jtag_update(pcie_port);
#पूर्ण_अगर

	/* Make sure we aren't trying to setup a target mode पूर्णांकerface in host mode */
	mio_rst_ctl.u64 = cvmx_पढ़ो_csr(CVMX_MIO_RST_CTLX(pcie_port));
	अगर (!mio_rst_ctl.s.host_mode) अणु
		pr_notice("PCIe: Port %d in endpoint mode.\n", pcie_port);
		वापस -1;
	पूर्ण

	/* CN63XX Pass 1.0 errata G-14395 requires the QLM De-emphasis be programmed */
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_0)) अणु
		अगर (pcie_port) अणु
			जोड़ cvmx_ciu_qlm ciu_qlm;
			ciu_qlm.u64 = cvmx_पढ़ो_csr(CVMX_CIU_QLM1);
			ciu_qlm.s.txbypass = 1;
			ciu_qlm.s.txdeemph = 5;
			ciu_qlm.s.txmargin = 0x17;
			cvmx_ग_लिखो_csr(CVMX_CIU_QLM1, ciu_qlm.u64);
		पूर्ण अन्यथा अणु
			जोड़ cvmx_ciu_qlm ciu_qlm;
			ciu_qlm.u64 = cvmx_पढ़ो_csr(CVMX_CIU_QLM0);
			ciu_qlm.s.txbypass = 1;
			ciu_qlm.s.txdeemph = 5;
			ciu_qlm.s.txmargin = 0x17;
			cvmx_ग_लिखो_csr(CVMX_CIU_QLM0, ciu_qlm.u64);
		पूर्ण
	पूर्ण
	/* Bring the PCIe out of reset */
	अगर (pcie_port)
		ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST1);
	अन्यथा
		ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST);
	/*
	 * After a chip reset the PCIe will also be in reset. If it
	 * isn't, most likely someone is trying to init it again
	 * without a proper PCIe reset
	 */
	अगर (ciu_soft_prst.s.soft_prst == 0) अणु
		/* Reset the port */
		ciu_soft_prst.s.soft_prst = 1;
		अगर (pcie_port)
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST1, ciu_soft_prst.u64);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST, ciu_soft_prst.u64);
		/* Wait until pcie resets the ports. */
		udelay(2000);
	पूर्ण
	अगर (pcie_port) अणु
		ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST1);
		ciu_soft_prst.s.soft_prst = 0;
		cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST1, ciu_soft_prst.u64);
	पूर्ण अन्यथा अणु
		ciu_soft_prst.u64 = cvmx_पढ़ो_csr(CVMX_CIU_SOFT_PRST);
		ciu_soft_prst.s.soft_prst = 0;
		cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_PRST, ciu_soft_prst.u64);
	पूर्ण

	/* Wait क्रम PCIe reset to complete */
	udelay(1000);

	/*
	 * Check and make sure PCIe came out of reset. If it करोesn't
	 * the board probably hasn't wired the घड़ीs up and the
	 * पूर्णांकerface should be skipped.
	 */
	अगर (CVMX_WAIT_FOR_FIELD64(CVMX_MIO_RST_CTLX(pcie_port), जोड़ cvmx_mio_rst_ctlx, rst_करोne, ==, 1, 10000)) अणु
		pr_notice("PCIe: Port %d stuck in reset, skipping.\n", pcie_port);
		वापस -1;
	पूर्ण

	/* Check BIST status */
	pemx_bist_status.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_BIST_STATUS(pcie_port));
	अगर (pemx_bist_status.u64)
		pr_notice("PCIe: BIST FAILED for port %d (0x%016llx)\n", pcie_port, CAST64(pemx_bist_status.u64));
	pemx_bist_status2.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_BIST_STATUS2(pcie_port));
	/* Errata PCIE-14766 may cause the lower 6 bits to be अक्रमomly set on CN63XXp1 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X))
		pemx_bist_status2.u64 &= ~0x3full;
	अगर (pemx_bist_status2.u64)
		pr_notice("PCIe: BIST2 FAILED for port %d (0x%016llx)\n", pcie_port, CAST64(pemx_bist_status2.u64));

	/* Initialize the config space CSRs */
	__cvmx_pcie_rc_initialize_config_space(pcie_port);

	/* Enable gen2 speed selection */
	pciercx_cfg515.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG515(pcie_port));
	pciercx_cfg515.s.dsc = 1;
	cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG515(pcie_port), pciercx_cfg515.u32);

	/* Bring the link up */
	अगर (__cvmx_pcie_rc_initialize_link_gen2(pcie_port)) अणु
		/*
		 * Some gen1 devices करोn't handle the gen 2 training
		 * correctly. Disable gen2 and try again with only
		 * gen1
		 */
		जोड़ cvmx_pciercx_cfg031 pciercx_cfg031;
		pciercx_cfg031.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG031(pcie_port));
		pciercx_cfg031.s.mls = 1;
		cvmx_pcie_cfgx_ग_लिखो(pcie_port, CVMX_PCIERCX_CFG031(pcie_port), pciercx_cfg031.u32);
		अगर (__cvmx_pcie_rc_initialize_link_gen2(pcie_port)) अणु
			pr_notice("PCIe: Link timeout on port %d, probably the slot is empty\n", pcie_port);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Store merge control (SLI_MEM_ACCESS_CTL[TIMER,MAX_WORD]) */
	sli_mem_access_ctl.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_SLI_MEM_ACCESS_CTL);
	sli_mem_access_ctl.s.max_word = 0;	/* Allow 16 words to combine */
	sli_mem_access_ctl.s.समयr = 127;	/* Wait up to 127 cycles क्रम more data */
	cvmx_ग_लिखो_csr(CVMX_PEXP_SLI_MEM_ACCESS_CTL, sli_mem_access_ctl.u64);

	/* Setup Mem access SubDIDs */
	mem_access_subid.u64 = 0;
	mem_access_subid.s.port = pcie_port; /* Port the request is sent to. */
	mem_access_subid.s.nmerge = 0;	/* Allow merging as it works on CN6XXX. */
	mem_access_subid.s.esr = 1;	/* Endian-swap क्रम Reads. */
	mem_access_subid.s.esw = 1;	/* Endian-swap क्रम Writes. */
	mem_access_subid.s.wtype = 0;	/* "No snoop" and "Relaxed ordering" are not set */
	mem_access_subid.s.rtype = 0;	/* "No snoop" and "Relaxed ordering" are not set */
	/* PCIe Adddress Bits <63:34>. */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
		mem_access_subid.cn68xx.ba = 0;
	अन्यथा
		mem_access_subid.s.ba = 0;

	/*
	 * Setup mem access 12-15 क्रम port 0, 16-19 क्रम port 1,
	 * supplying 36 bits of address space.
	 */
	क्रम (i = 12 + pcie_port * 4; i < 16 + pcie_port * 4; i++) अणु
		cvmx_ग_लिखो_csr(CVMX_PEXP_SLI_MEM_ACCESS_SUBIDX(i), mem_access_subid.u64);
		/* Set each SUBID to extend the addressable range */
		__cvmx_increment_ba(&mem_access_subid);
	पूर्ण

	/*
	 * Disable the peer to peer क्रमwarding रेजिस्टर. This must be
	 * setup by the OS after it क्रमागतerates the bus and assigns
	 * addresses to the PCIe busses.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		cvmx_ग_लिखो_csr(CVMX_PEMX_P2P_BARX_START(i, pcie_port), -1);
		cvmx_ग_लिखो_csr(CVMX_PEMX_P2P_BARX_END(i, pcie_port), -1);
	पूर्ण

	/* Set Octeon's BAR0 to decode 0-16KB. It overlaps with Bar2 */
	cvmx_ग_लिखो_csr(CVMX_PEMX_P2N_BAR0_START(pcie_port), 0);

	/*
	 * Set Octeon's BAR2 to decode 0-2^41. Bar0 and Bar1 take
	 * precedence where they overlap. It also overlaps with the
	 * device addresses, so make sure the peer to peer क्रमwarding
	 * is set right.
	 */
	cvmx_ग_लिखो_csr(CVMX_PEMX_P2N_BAR2_START(pcie_port), 0);

	/*
	 * Setup BAR2 attributes
	 * Relaxed Ordering (NPEI_CTL_PORTn[PTLP_RO,CTLP_RO, WAIT_COM])
	 * - PTLP_RO,CTLP_RO should normally be set (except क्रम debug).
	 * - WAIT_COM=0 will likely work क्रम all applications.
	 * Load completion relaxed ordering (NPEI_CTL_PORTn[WAITL_COM])
	 */
	pemx_bar_ctl.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_BAR_CTL(pcie_port));
	pemx_bar_ctl.s.bar1_siz = 3;  /* 256MB BAR1*/
	pemx_bar_ctl.s.bar2_enb = 1;
	pemx_bar_ctl.s.bar2_esx = 1;
	pemx_bar_ctl.s.bar2_cax = 0;
	cvmx_ग_लिखो_csr(CVMX_PEMX_BAR_CTL(pcie_port), pemx_bar_ctl.u64);
	sli_ctl_portx.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_SLI_CTL_PORTX(pcie_port));
	sli_ctl_portx.s.ptlp_ro = 1;
	sli_ctl_portx.s.ctlp_ro = 1;
	sli_ctl_portx.s.रुको_com = 0;
	sli_ctl_portx.s.रुकोl_com = 0;
	cvmx_ग_लिखो_csr(CVMX_PEXP_SLI_CTL_PORTX(pcie_port), sli_ctl_portx.u64);

	/* BAR1 follows BAR2 */
	cvmx_ग_लिखो_csr(CVMX_PEMX_P2N_BAR1_START(pcie_port), CVMX_PCIE_BAR1_RC_BASE);

	bar1_index.u64 = 0;
	bar1_index.s.addr_idx = (CVMX_PCIE_BAR1_PHYS_BASE >> 22);
	bar1_index.s.ca = 1;	   /* Not Cached */
	bar1_index.s.end_swp = 1;  /* Endian Swap mode */
	bar1_index.s.addr_v = 1;   /* Valid entry */

	क्रम (i = 0; i < 16; i++) अणु
		cvmx_ग_लिखो_csr(CVMX_PEMX_BAR1_INDEXX(i, pcie_port), bar1_index.u64);
		/* 256MB / 16 >> 22 == 4 */
		bar1_index.s.addr_idx += (((1ull << 28) / 16ull) >> 22);
	पूर्ण

	/*
	 * Allow config retries क्रम 250ms. Count is based off the 5Ghz
	 * SERDES घड़ी.
	 */
	pemx_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_CTL_STATUS(pcie_port));
	pemx_ctl_status.s.cfg_rtry = 250 * 5000000 / 0x10000;
	cvmx_ग_लिखो_csr(CVMX_PEMX_CTL_STATUS(pcie_port), pemx_ctl_status.u64);

	/* Display the link status */
	pciercx_cfg032.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	pr_notice("PCIe: Port %d link active, %d lanes, speed gen%d\n", pcie_port, pciercx_cfg032.s.nlw, pciercx_cfg032.s.ls);

	वापस 0;
पूर्ण

/**
 * Initialize a PCIe port क्रम use in host(RC) mode. It करोesn't क्रमागतerate the bus.
 *
 * @pcie_port: PCIe port to initialize
 *
 * Returns Zero on success
 */
अटल पूर्णांक cvmx_pcie_rc_initialize(पूर्णांक pcie_port)
अणु
	पूर्णांक result;
	अगर (octeon_has_feature(OCTEON_FEATURE_NPEI))
		result = __cvmx_pcie_rc_initialize_gen1(pcie_port);
	अन्यथा
		result = __cvmx_pcie_rc_initialize_gen2(pcie_port);
	वापस result;
पूर्ण

/* Above was cvmx-pcie.c, below original pcie.c */

/**
 * Map a PCI device to the appropriate पूर्णांकerrupt line
 *
 * @dev:    The Linux PCI device काष्ठाure क्रम the device to map
 * @slot:   The slot number क्रम this device on __BUS 0__. Linux
 *		 क्रमागतerates through all the bridges and figures out the
 *		 slot on Bus 0 where this device eventually hooks to.
 * @pin:    The PCI पूर्णांकerrupt pin पढ़ो from the device, then swizzled
 *		 as it goes through each bridge.
 * Returns Interrupt number क्रम the device
 */
पूर्णांक octeon_pcie_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	/*
	 * The EBH5600 board with the PCI to PCIe bridge mistakenly
	 * wires the first slot क्रम both device id 2 and पूर्णांकerrupt
	 * A. According to the PCI spec, device id 2 should be C. The
	 * following kludge attempts to fix this.
	 */
	अगर (म_माला(octeon_board_type_string(), "EBH5600") &&
	    dev->bus && dev->bus->parent) अणु
		/*
		 * Iterate all the way up the device chain and find
		 * the root bus.
		 */
		जबतक (dev->bus && dev->bus->parent)
			dev = to_pci_dev(dev->bus->bridge);
		/*
		 * If the root bus is number 0 and the PEX 8114 is the
		 * root, assume we are behind the miswired bus. We
		 * need to correct the swizzle level by two. Yuck.
		 */
		अगर ((dev->bus->number == 1) &&
		    (dev->venकरोr == 0x10b5) && (dev->device == 0x8114)) अणु
			/*
			 * The pin field is one based, not zero. We
			 * need to swizzle it by minus two.
			 */
			pin = ((pin - 3) & 3) + 1;
		पूर्ण
	पूर्ण
	/*
	 * The -1 is because pin starts with one, not zero. It might
	 * be that this equation needs to include the slot number, but
	 * I करोn't have hardware to check that against.
	 */
	वापस pin - 1 + OCTEON_IRQ_PCI_INT0;
पूर्ण

अटल	व्योम set_cfg_पढ़ो_retry(u32 retry_cnt)
अणु
	जोड़ cvmx_pemx_ctl_status pemx_ctl;
	pemx_ctl.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_CTL_STATUS(1));
	pemx_ctl.s.cfg_rtry = retry_cnt;
	cvmx_ग_लिखो_csr(CVMX_PEMX_CTL_STATUS(1), pemx_ctl.u64);
पूर्ण


अटल u32 disable_cfg_पढ़ो_retry(व्योम)
अणु
	u32 retry_cnt;

	जोड़ cvmx_pemx_ctl_status pemx_ctl;
	pemx_ctl.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_CTL_STATUS(1));
	retry_cnt =  pemx_ctl.s.cfg_rtry;
	pemx_ctl.s.cfg_rtry = 0;
	cvmx_ग_लिखो_csr(CVMX_PEMX_CTL_STATUS(1), pemx_ctl.u64);
	वापस retry_cnt;
पूर्ण

अटल पूर्णांक is_cfg_retry(व्योम)
अणु
	जोड़ cvmx_pemx_पूर्णांक_sum pemx_पूर्णांक_sum;
	pemx_पूर्णांक_sum.u64 = cvmx_पढ़ो_csr(CVMX_PEMX_INT_SUM(1));
	अगर (pemx_पूर्णांक_sum.s.crs_dr)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Read a value from configuration space
 *
 */
अटल पूर्णांक octeon_pcie_पढ़ो_config(अचिन्हित पूर्णांक pcie_port, काष्ठा pci_bus *bus,
				   अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक size,
				   u32 *val)
अणु
	जोड़ octeon_cvmemctl cvmmemctl;
	जोड़ octeon_cvmemctl cvmmemctl_save;
	पूर्णांक bus_number = bus->number;
	पूर्णांक cfg_retry = 0;
	पूर्णांक retry_cnt = 0;
	पूर्णांक max_retry_cnt = 10;
	u32 cfg_retry_cnt = 0;

	cvmmemctl_save.u64 = 0;
	BUG_ON(pcie_port >= ARRAY_SIZE(enable_pcie_bus_num_war));
	/*
	 * For the top level bus make sure our hardware bus number
	 * matches the software one
	 */
	अगर (bus->parent == शून्य) अणु
		अगर (enable_pcie_bus_num_war[pcie_port])
			bus_number = 0;
		अन्यथा अणु
			जोड़ cvmx_pciercx_cfg006 pciercx_cfg006;
			pciercx_cfg006.u32 = cvmx_pcie_cfgx_पढ़ो(pcie_port,
					     CVMX_PCIERCX_CFG006(pcie_port));
			अगर (pciercx_cfg006.s.pbnum != bus_number) अणु
				pciercx_cfg006.s.pbnum = bus_number;
				pciercx_cfg006.s.sbnum = bus_number;
				pciercx_cfg006.s.subbnum = bus_number;
				cvmx_pcie_cfgx_ग_लिखो(pcie_port,
					    CVMX_PCIERCX_CFG006(pcie_port),
					    pciercx_cfg006.u32);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * PCIe only has a single device connected to Octeon. It is
	 * always device ID 0. Don't bother करोing पढ़ोs क्रम other
	 * device IDs on the first segment.
	 */
	अगर ((bus->parent == शून्य) && (devfn >> 3 != 0))
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;

	/*
	 * The following is a workaround क्रम the CN57XX, CN56XX,
	 * CN55XX, and CN54XX errata with PCIe config पढ़ोs from non
	 * existent devices.  These chips will hang the PCIe link अगर a
	 * config पढ़ो is perक्रमmed that causes a UR response.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_1)) अणु
		/*
		 * For our EBH5600 board, port 0 has a bridge with two
		 * PCI-X slots. We need a new special checks to make
		 * sure we only probe valid stuff.  The PCIe->PCI-X
		 * bridge only respondes to device ID 0, function
		 * 0-1
		 */
		अगर ((bus->parent == शून्य) && (devfn >= 2))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
		/*
		 * The PCI-X slots are device ID 2,3. Choose one of
		 * the below "if" blocks based on what is plugged पूर्णांकo
		 * the board.
		 */
#अगर 1
		/* Use this option अगर you aren't using either slot */
		अगर (bus_number == 2)
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
#या_अगर 0
		/*
		 * Use this option अगर you are using the first slot but
		 * not the second.
		 */
		अगर ((bus_number == 2) && (devfn >> 3 != 2))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
#या_अगर 0
		/*
		 * Use this option अगर you are using the second slot
		 * but not the first.
		 */
		अगर ((bus_number == 2) && (devfn >> 3 != 3))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
#या_अगर 0
		/* Use this opion अगर you are using both slots */
		अगर ((bus_number == 2) &&
		    !((devfn == (2 << 3)) || (devfn == (3 << 3))))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
#पूर्ण_अगर

		/* The following #अगर gives a more complicated example. This is
		   the required checks क्रम running a Nitrox CN16XX-NHBX in the
		   slot of the EBH5600. This card has a PLX PCIe bridge with
		   four Nitrox PLX parts behind it */
#अगर 0
		/* PLX bridge with 4 ports */
		अगर ((bus_number == 4) &&
		    !((devfn >> 3 >= 1) && (devfn >> 3 <= 4)))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 1 */
		अगर ((bus_number == 5) && (devfn >> 3 != 0))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 2 */
		अगर ((bus_number == 6) && (devfn >> 3 != 0))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 3 */
		अगर ((bus_number == 7) && (devfn >> 3 != 0))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 4 */
		अगर ((bus_number == 8) && (devfn >> 3 != 0))
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
#पूर्ण_अगर

		/*
		 * Shorten the DID समयout so bus errors क्रम PCIe
		 * config पढ़ोs from non existent devices happen
		 * faster. This allows us to जारी booting even अगर
		 * the above "if" checks are wrong.  Once one of these
		 * errors happens, the PCIe port is dead.
		 */
		cvmmemctl_save.u64 = __पढ़ो_64bit_c0_रेजिस्टर($11, 7);
		cvmmemctl.u64 = cvmmemctl_save.u64;
		cvmmemctl.s.didtto = 2;
		__ग_लिखो_64bit_c0_रेजिस्टर($11, 7, cvmmemctl.u64);
	पूर्ण

	अगर ((OCTEON_IS_MODEL(OCTEON_CN63XX)) && (enable_pcie_14459_war))
		cfg_retry_cnt = disable_cfg_पढ़ो_retry();

	pr_debug("pcie_cfg_rd port=%d b=%d devfn=0x%03x reg=0x%03x"
		 " size=%d ", pcie_port, bus_number, devfn, reg, size);
	करो अणु
		चयन (size) अणु
		हाल 4:
			*val = cvmx_pcie_config_पढ़ो32(pcie_port, bus_number,
				devfn >> 3, devfn & 0x7, reg);
		अवरोध;
		हाल 2:
			*val = cvmx_pcie_config_पढ़ो16(pcie_port, bus_number,
				devfn >> 3, devfn & 0x7, reg);
		अवरोध;
		हाल 1:
			*val = cvmx_pcie_config_पढ़ो8(pcie_port, bus_number,
				devfn >> 3, devfn & 0x7, reg);
		अवरोध;
		शेष:
			अगर (OCTEON_IS_MODEL(OCTEON_CN63XX))
				set_cfg_पढ़ो_retry(cfg_retry_cnt);
			वापस PCIBIOS_FUNC_NOT_SUPPORTED;
		पूर्ण
		अगर ((OCTEON_IS_MODEL(OCTEON_CN63XX)) &&
			(enable_pcie_14459_war)) अणु
			cfg_retry = is_cfg_retry();
			retry_cnt++;
			अगर (retry_cnt > max_retry_cnt) अणु
				pr_err(" pcie cfg_read retries failed. retry_cnt=%d\n",
				       retry_cnt);
				cfg_retry = 0;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (cfg_retry);

	अगर ((OCTEON_IS_MODEL(OCTEON_CN63XX)) && (enable_pcie_14459_war))
		set_cfg_पढ़ो_retry(cfg_retry_cnt);
	pr_debug("val=%08x  : tries=%02d\n", *val, retry_cnt);
	अगर (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_1))
		ग_लिखो_c0_cvmmemctl(cvmmemctl_save.u64);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक octeon_pcie0_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	वापस octeon_pcie_पढ़ो_config(0, bus, devfn, reg, size, val);
पूर्ण

अटल पूर्णांक octeon_pcie1_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	वापस octeon_pcie_पढ़ो_config(1, bus, devfn, reg, size, val);
पूर्ण

अटल पूर्णांक octeon_dummy_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	वापस PCIBIOS_FUNC_NOT_SUPPORTED;
पूर्ण

/*
 * Write a value to PCI configuration space
 */
अटल पूर्णांक octeon_pcie_ग_लिखो_config(अचिन्हित पूर्णांक pcie_port, काष्ठा pci_bus *bus,
				    अचिन्हित पूर्णांक devfn, पूर्णांक reg,
				    पूर्णांक size, u32 val)
अणु
	पूर्णांक bus_number = bus->number;

	BUG_ON(pcie_port >= ARRAY_SIZE(enable_pcie_bus_num_war));

	अगर ((bus->parent == शून्य) && (enable_pcie_bus_num_war[pcie_port]))
		bus_number = 0;

	pr_debug("pcie_cfg_wr port=%d b=%d devfn=0x%03x"
		 " reg=0x%03x size=%d val=%08x\n", pcie_port, bus_number, devfn,
		 reg, size, val);


	चयन (size) अणु
	हाल 4:
		cvmx_pcie_config_ग_लिखो32(pcie_port, bus_number, devfn >> 3,
					 devfn & 0x7, reg, val);
		अवरोध;
	हाल 2:
		cvmx_pcie_config_ग_लिखो16(pcie_port, bus_number, devfn >> 3,
					 devfn & 0x7, reg, val);
		अवरोध;
	हाल 1:
		cvmx_pcie_config_ग_लिखो8(pcie_port, bus_number, devfn >> 3,
					devfn & 0x7, reg, val);
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक octeon_pcie0_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	वापस octeon_pcie_ग_लिखो_config(0, bus, devfn, reg, size, val);
पूर्ण

अटल पूर्णांक octeon_pcie1_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	वापस octeon_pcie_ग_लिखो_config(1, bus, devfn, reg, size, val);
पूर्ण

अटल पूर्णांक octeon_dummy_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	वापस PCIBIOS_FUNC_NOT_SUPPORTED;
पूर्ण

अटल काष्ठा pci_ops octeon_pcie0_ops = अणु
	.पढ़ो	= octeon_pcie0_पढ़ो_config,
	.ग_लिखो	= octeon_pcie0_ग_लिखो_config,
पूर्ण;

अटल काष्ठा resource octeon_pcie0_mem_resource = अणु
	.name = "Octeon PCIe0 MEM",
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource octeon_pcie0_io_resource = अणु
	.name = "Octeon PCIe0 IO",
	.flags = IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller octeon_pcie0_controller = अणु
	.pci_ops = &octeon_pcie0_ops,
	.mem_resource = &octeon_pcie0_mem_resource,
	.io_resource = &octeon_pcie0_io_resource,
पूर्ण;

अटल काष्ठा pci_ops octeon_pcie1_ops = अणु
	.पढ़ो	= octeon_pcie1_पढ़ो_config,
	.ग_लिखो	= octeon_pcie1_ग_लिखो_config,
पूर्ण;

अटल काष्ठा resource octeon_pcie1_mem_resource = अणु
	.name = "Octeon PCIe1 MEM",
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource octeon_pcie1_io_resource = अणु
	.name = "Octeon PCIe1 IO",
	.flags = IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller octeon_pcie1_controller = अणु
	.pci_ops = &octeon_pcie1_ops,
	.mem_resource = &octeon_pcie1_mem_resource,
	.io_resource = &octeon_pcie1_io_resource,
पूर्ण;

अटल काष्ठा pci_ops octeon_dummy_ops = अणु
	.पढ़ो	= octeon_dummy_पढ़ो_config,
	.ग_लिखो	= octeon_dummy_ग_लिखो_config,
पूर्ण;

अटल काष्ठा resource octeon_dummy_mem_resource = अणु
	.name = "Virtual PCIe MEM",
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource octeon_dummy_io_resource = अणु
	.name = "Virtual PCIe IO",
	.flags = IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller octeon_dummy_controller = अणु
	.pci_ops = &octeon_dummy_ops,
	.mem_resource = &octeon_dummy_mem_resource,
	.io_resource = &octeon_dummy_io_resource,
पूर्ण;

अटल पूर्णांक device_needs_bus_num_war(uपूर्णांक32_t deviceid)
अणु
#घोषणा IDT_VENDOR_ID 0x111d

	अगर ((deviceid  & 0xffff) == IDT_VENDOR_ID)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * Initialize the Octeon PCIe controllers
 *
 * Returns
 */
अटल पूर्णांक __init octeon_pcie_setup(व्योम)
अणु
	पूर्णांक result;
	पूर्णांक host_mode;
	पूर्णांक srio_war15205 = 0, port;
	जोड़ cvmx_sli_ctl_portx sli_ctl_portx;
	जोड़ cvmx_sriox_status_reg sriox_status_reg;

	/* These chips करोn't have PCIe */
	अगर (!octeon_has_feature(OCTEON_FEATURE_PCIE))
		वापस 0;

	/* No PCIe simulation */
	अगर (octeon_is_simulation())
		वापस 0;

	/* Disable PCI अगर inकाष्ठाed on the command line */
	अगर (pcie_disable)
		वापस 0;

	/* Poपूर्णांक pcibios_map_irq() to the PCIe version of it */
	octeon_pcibios_map_irq = octeon_pcie_pcibios_map_irq;

	/*
	 * PCIe I/O range. It is based on port 0 but includes up until
	 * port 1's end.
	 */
	set_io_port_base(CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(0)));
	ioport_resource.start = 0;
	ioport_resource.end =
		cvmx_pcie_get_io_base_address(1) -
		cvmx_pcie_get_io_base_address(0) + cvmx_pcie_get_io_size(1) - 1;

	/*
	 * Create a dummy PCIe controller to swallow up bus 0. IDT bridges
	 * करोn't work अगर the primary bus number is zero. Here we add a fake
	 * PCIe controller that the kernel will give bus 0. This allows
	 * us to not change the normal kernel bus क्रमागतeration
	 */
	octeon_dummy_controller.io_map_base = -1;
	octeon_dummy_controller.mem_resource->start = (1ull<<48);
	octeon_dummy_controller.mem_resource->end = (1ull<<48);
	रेजिस्टर_pci_controller(&octeon_dummy_controller);

	अगर (octeon_has_feature(OCTEON_FEATURE_NPEI)) अणु
		जोड़ cvmx_npei_ctl_status npei_ctl_status;
		npei_ctl_status.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_CTL_STATUS);
		host_mode = npei_ctl_status.s.host_mode;
		octeon_dma_bar_type = OCTEON_DMA_BAR_TYPE_PCIE;
	पूर्ण अन्यथा अणु
		जोड़ cvmx_mio_rst_ctlx mio_rst_ctl;
		mio_rst_ctl.u64 = cvmx_पढ़ो_csr(CVMX_MIO_RST_CTLX(0));
		host_mode = mio_rst_ctl.s.host_mode;
		octeon_dma_bar_type = OCTEON_DMA_BAR_TYPE_PCIE2;
	पूर्ण

	अगर (host_mode) अणु
		pr_notice("PCIe: Initializing port 0\n");
		/* CN63XX pass 1_x/2.0 errata PCIe-15205 */
		अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) अणु
			sriox_status_reg.u64 = cvmx_पढ़ो_csr(CVMX_SRIOX_STATUS_REG(0));
			अगर (sriox_status_reg.s.srio) अणु
				srio_war15205 += 1;	 /* Port is SRIO */
				port = 0;
			पूर्ण
		पूर्ण
		result = cvmx_pcie_rc_initialize(0);
		अगर (result == 0) अणु
			uपूर्णांक32_t device0;
			/* Memory offsets are physical addresses */
			octeon_pcie0_controller.mem_offset =
				cvmx_pcie_get_mem_base_address(0);
			/* IO offsets are Mips भव addresses */
			octeon_pcie0_controller.io_map_base =
				CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address
						(0));
			octeon_pcie0_controller.io_offset = 0;
			/*
			 * To keep things similar to PCI, we start
			 * device addresses at the same place as PCI
			 * uisng big bar support. This normally
			 * translates to 4GB-256MB, which is the same
			 * as most x86 PCs.
			 */
			octeon_pcie0_controller.mem_resource->start =
				cvmx_pcie_get_mem_base_address(0) +
				(4ul << 30) - (OCTEON_PCI_BAR1_HOLE_SIZE << 20);
			octeon_pcie0_controller.mem_resource->end =
				cvmx_pcie_get_mem_base_address(0) +
				cvmx_pcie_get_mem_size(0) - 1;
			/*
			 * Ports must be above 16KB क्रम the ISA bus
			 * filtering in the PCI-X to PCI bridge.
			 */
			octeon_pcie0_controller.io_resource->start = 4 << 10;
			octeon_pcie0_controller.io_resource->end =
				cvmx_pcie_get_io_size(0) - 1;
			msleep(100); /* Some devices need extra समय */
			रेजिस्टर_pci_controller(&octeon_pcie0_controller);
			device0 = cvmx_pcie_config_पढ़ो32(0, 0, 0, 0, 0);
			enable_pcie_bus_num_war[0] =
				device_needs_bus_num_war(device0);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_notice("PCIe: Port 0 in endpoint mode, skipping.\n");
		/* CN63XX pass 1_x/2.0 errata PCIe-15205 */
		अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) अणु
			srio_war15205 += 1;
			port = 0;
		पूर्ण
	पूर्ण

	अगर (octeon_has_feature(OCTEON_FEATURE_NPEI)) अणु
		host_mode = 1;
		/* Skip the 2nd port on CN52XX अगर port 0 is in 4 lane mode */
		अगर (OCTEON_IS_MODEL(OCTEON_CN52XX)) अणु
			जोड़ cvmx_npei_dbg_data dbg_data;
			dbg_data.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_NPEI_DBG_DATA);
			अगर (dbg_data.cn52xx.qlm0_link_width)
				host_mode = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		जोड़ cvmx_mio_rst_ctlx mio_rst_ctl;
		mio_rst_ctl.u64 = cvmx_पढ़ो_csr(CVMX_MIO_RST_CTLX(1));
		host_mode = mio_rst_ctl.s.host_mode;
	पूर्ण

	अगर (host_mode) अणु
		pr_notice("PCIe: Initializing port 1\n");
		/* CN63XX pass 1_x/2.0 errata PCIe-15205 */
		अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) अणु
			sriox_status_reg.u64 = cvmx_पढ़ो_csr(CVMX_SRIOX_STATUS_REG(1));
			अगर (sriox_status_reg.s.srio) अणु
				srio_war15205 += 1;	 /* Port is SRIO */
				port = 1;
			पूर्ण
		पूर्ण
		result = cvmx_pcie_rc_initialize(1);
		अगर (result == 0) अणु
			uपूर्णांक32_t device0;
			/* Memory offsets are physical addresses */
			octeon_pcie1_controller.mem_offset =
				cvmx_pcie_get_mem_base_address(1);
			/*
			 * To calculate the address क्रम accessing the 2nd PCIe device,
			 * either 'io_map_base' (pci_iomap()), or 'mips_io_port_base'
			 * (ioport_map()) value is added to
			 * pci_resource_start(dev,bar)). The 'mips_io_port_base' is set
			 * only once based on first PCIe. Also changing 'io_map_base'
			 * based on first slot's value so that both the routines will
			 * work properly.
			 */
			octeon_pcie1_controller.io_map_base =
				CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(0));
			/* IO offsets are Mips भव addresses */
			octeon_pcie1_controller.io_offset =
				cvmx_pcie_get_io_base_address(1) -
				cvmx_pcie_get_io_base_address(0);
			/*
			 * To keep things similar to PCI, we start device
			 * addresses at the same place as PCI uisng big bar
			 * support. This normally translates to 4GB-256MB,
			 * which is the same as most x86 PCs.
			 */
			octeon_pcie1_controller.mem_resource->start =
				cvmx_pcie_get_mem_base_address(1) + (4ul << 30) -
				(OCTEON_PCI_BAR1_HOLE_SIZE << 20);
			octeon_pcie1_controller.mem_resource->end =
				cvmx_pcie_get_mem_base_address(1) +
				cvmx_pcie_get_mem_size(1) - 1;
			/*
			 * Ports must be above 16KB क्रम the ISA bus filtering
			 * in the PCI-X to PCI bridge.
			 */
			octeon_pcie1_controller.io_resource->start =
				cvmx_pcie_get_io_base_address(1) -
				cvmx_pcie_get_io_base_address(0);
			octeon_pcie1_controller.io_resource->end =
				octeon_pcie1_controller.io_resource->start +
				cvmx_pcie_get_io_size(1) - 1;
			msleep(100); /* Some devices need extra समय */
			रेजिस्टर_pci_controller(&octeon_pcie1_controller);
			device0 = cvmx_pcie_config_पढ़ो32(1, 0, 0, 0, 0);
			enable_pcie_bus_num_war[1] =
				device_needs_bus_num_war(device0);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_notice("PCIe: Port 1 not in root complex mode, skipping.\n");
		/* CN63XX pass 1_x/2.0 errata PCIe-15205  */
		अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) अणु
			srio_war15205 += 1;
			port = 1;
		पूर्ण
	पूर्ण

	/*
	 * CN63XX pass 1_x/2.0 errata PCIe-15205 requires setting all
	 * of SRIO MACs SLI_CTL_PORT*[INT*_MAP] to similar value and
	 * all of PCIe Macs SLI_CTL_PORT*[INT*_MAP] to dअगरferent value
	 * from the previous set values
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
		OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) अणु
		अगर (srio_war15205 == 1) अणु
			sli_ctl_portx.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_SLI_CTL_PORTX(port));
			sli_ctl_portx.s.पूर्णांकa_map = 1;
			sli_ctl_portx.s.पूर्णांकb_map = 1;
			sli_ctl_portx.s.पूर्णांकc_map = 1;
			sli_ctl_portx.s.पूर्णांकd_map = 1;
			cvmx_ग_लिखो_csr(CVMX_PEXP_SLI_CTL_PORTX(port), sli_ctl_portx.u64);

			sli_ctl_portx.u64 = cvmx_पढ़ो_csr(CVMX_PEXP_SLI_CTL_PORTX(!port));
			sli_ctl_portx.s.पूर्णांकa_map = 0;
			sli_ctl_portx.s.पूर्णांकb_map = 0;
			sli_ctl_portx.s.पूर्णांकc_map = 0;
			sli_ctl_portx.s.पूर्णांकd_map = 0;
			cvmx_ग_लिखो_csr(CVMX_PEXP_SLI_CTL_PORTX(!port), sli_ctl_portx.u64);
		पूर्ण
	पूर्ण

	octeon_pci_dma_init();

	वापस 0;
पूर्ण
arch_initcall(octeon_pcie_setup);
