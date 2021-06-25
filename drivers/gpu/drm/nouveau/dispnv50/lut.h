<शैली गुरु>
#अगर_अघोषित __NV50_KMS_LUT_H__
#घोषणा __NV50_KMS_LUT_H__
#समावेश <nvअगर/स्मृति.स>
काष्ठा drm_property_blob;
काष्ठा drm_color_lut;
काष्ठा nv50_disp;

काष्ठा nv50_lut अणु
	काष्ठा nvअगर_mem mem[2];
पूर्ण;

पूर्णांक nv50_lut_init(काष्ठा nv50_disp *, काष्ठा nvअगर_mmu *, काष्ठा nv50_lut *);
व्योम nv50_lut_fini(काष्ठा nv50_lut *);
u32 nv50_lut_load(काष्ठा nv50_lut *, पूर्णांक buffer, काष्ठा drm_property_blob *,
		  व्योम (*)(काष्ठा drm_color_lut *, पूर्णांक size, व्योम __iomem *));
#पूर्ण_अगर
