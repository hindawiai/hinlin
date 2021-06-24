<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_GPIO_PRIV_H__
#घोषणा __NVKM_GPIO_PRIV_H__
#घोषणा nvkm_gpio(p) container_of((p), काष्ठा nvkm_gpio, subdev)
#समावेश <subdev/gpपन.स>

काष्ठा nvkm_gpio_func अणु
	पूर्णांक lines;

	/* पढ़ो and ack pending पूर्णांकerrupts, वापसing only data
	 * क्रम lines that have not been masked off, जबतक still
	 * perक्रमming the ack क्रम anything that was pending.
	 */
	व्योम (*पूर्णांकr_stat)(काष्ठा nvkm_gpio *, u32 *, u32 *);

	/* mask on/off पूर्णांकerrupts क्रम hi/lo transitions on a
	 * given set of gpio lines
	 */
	व्योम (*पूर्णांकr_mask)(काष्ठा nvkm_gpio *, u32, u32, u32);

	/* configure gpio direction and output value */
	पूर्णांक  (*drive)(काष्ठा nvkm_gpio *, पूर्णांक line, पूर्णांक dir, पूर्णांक out);

	/* sense current state of given gpio line */
	पूर्णांक  (*sense)(काष्ठा nvkm_gpio *, पूर्णांक line);

	/*XXX*/
	व्योम (*reset)(काष्ठा nvkm_gpio *, u8);
पूर्ण;

पूर्णांक nvkm_gpio_new_(स्थिर काष्ठा nvkm_gpio_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		   काष्ठा nvkm_gpio **);

व्योम nv50_gpio_reset(काष्ठा nvkm_gpio *, u8);
पूर्णांक  nv50_gpio_drive(काष्ठा nvkm_gpio *, पूर्णांक, पूर्णांक, पूर्णांक);
पूर्णांक  nv50_gpio_sense(काष्ठा nvkm_gpio *, पूर्णांक);

व्योम g94_gpio_पूर्णांकr_stat(काष्ठा nvkm_gpio *, u32 *, u32 *);
व्योम g94_gpio_पूर्णांकr_mask(काष्ठा nvkm_gpio *, u32, u32, u32);

व्योम gf119_gpio_reset(काष्ठा nvkm_gpio *, u8);
पूर्णांक  gf119_gpio_drive(काष्ठा nvkm_gpio *, पूर्णांक, पूर्णांक, पूर्णांक);
पूर्णांक  gf119_gpio_sense(काष्ठा nvkm_gpio *, पूर्णांक);
#पूर्ण_अगर
