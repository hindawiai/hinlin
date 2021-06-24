<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_AGP_BACKEND_H
#घोषणा _ALPHA_AGP_BACKEND_H 1

प्रकार	जोड़ _alpha_agp_mode अणु
	काष्ठा अणु
		u32 rate : 3;
		u32 reserved0 : 1;
		u32 fw : 1;
		u32 fourgb : 1;
		u32 reserved1 : 2;
		u32 enable : 1;
		u32 sba : 1;
		u32 reserved2 : 14;
		u32 rq : 8;
	पूर्ण bits;
	u32 lw;
पूर्ण alpha_agp_mode;

प्रकार काष्ठा _alpha_agp_info अणु
	काष्ठा pci_controller *hose;
	काष्ठा अणु
		dma_addr_t bus_base;
		अचिन्हित दीर्घ size;
		व्योम *sysdata;
	पूर्ण aperture;
	alpha_agp_mode capability;
	alpha_agp_mode mode;
	व्योम *निजी;
	काष्ठा alpha_agp_ops *ops;
पूर्ण alpha_agp_info;

काष्ठा alpha_agp_ops अणु
	पूर्णांक (*setup)(alpha_agp_info *);
	व्योम (*cleanup)(alpha_agp_info *);
	पूर्णांक (*configure)(alpha_agp_info *);
	पूर्णांक (*bind)(alpha_agp_info *, off_t, काष्ठा agp_memory *);
	पूर्णांक (*unbind)(alpha_agp_info *, off_t, काष्ठा agp_memory *);
	अचिन्हित दीर्घ (*translate)(alpha_agp_info *, dma_addr_t);
पूर्ण;


#पूर्ण_अगर /* _ALPHA_AGP_BACKEND_H */
