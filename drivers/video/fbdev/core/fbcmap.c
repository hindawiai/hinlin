<शैली गुरु>
/*
 *  linux/drivers/video/fbcmap.c -- Colormap handling क्रम frame buffer devices
 *
 *	Created 15 Jun 1997 by Geert Uytterhoeven
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

अटल u16 red2[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa
पूर्ण;
अटल u16 green2[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa
पूर्ण;
अटल u16 blue2[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa
पूर्ण;

अटल u16 red4[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa, 0x5555, 0xffff
पूर्ण;
अटल u16 green4[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa, 0x5555, 0xffff
पूर्ण;
अटल u16 blue4[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa, 0x5555, 0xffff
पूर्ण;

अटल u16 red8[] __पढ़ो_mostly = अणु
    0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa
पूर्ण;
अटल u16 green8[] __पढ़ो_mostly = अणु
    0x0000, 0x0000, 0xaaaa, 0xaaaa, 0x0000, 0x0000, 0x5555, 0xaaaa
पूर्ण;
अटल u16 blue8[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa
पूर्ण;

अटल u16 red16[] __पढ़ो_mostly = अणु
    0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xaaaa, 0xaaaa, 0xaaaa,
    0x5555, 0x5555, 0x5555, 0x5555, 0xffff, 0xffff, 0xffff, 0xffff
पूर्ण;
अटल u16 green16[] __पढ़ो_mostly = अणु
    0x0000, 0x0000, 0xaaaa, 0xaaaa, 0x0000, 0x0000, 0x5555, 0xaaaa,
    0x5555, 0x5555, 0xffff, 0xffff, 0x5555, 0x5555, 0xffff, 0xffff
पूर्ण;
अटल u16 blue16[] __पढ़ो_mostly = अणु
    0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa, 0x0000, 0xaaaa,
    0x5555, 0xffff, 0x5555, 0xffff, 0x5555, 0xffff, 0x5555, 0xffff
पूर्ण;

अटल स्थिर काष्ठा fb_cmap शेष_2_colors = अणु
    .len=2, .red=red2, .green=green2, .blue=blue2
पूर्ण;
अटल स्थिर काष्ठा fb_cmap शेष_8_colors = अणु
    .len=8, .red=red8, .green=green8, .blue=blue8
पूर्ण;
अटल स्थिर काष्ठा fb_cmap शेष_4_colors = अणु
    .len=4, .red=red4, .green=green4, .blue=blue4
पूर्ण;
अटल स्थिर काष्ठा fb_cmap शेष_16_colors = अणु
    .len=16, .red=red16, .green=green16, .blue=blue16
पूर्ण;



/**
 *	fb_alloc_cmap_gfp - allocate a colormap
 *	@cmap: frame buffer colormap काष्ठाure
 *	@len: length of @cmap
 *	@transp: boolean, 1 अगर there is transparency, 0 otherwise
 *	@flags: flags क्रम kदो_स्मृति memory allocation
 *
 *	Allocates memory क्रम a colormap @cmap.  @len is the
 *	number of entries in the palette.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 *
 */

पूर्णांक fb_alloc_cmap_gfp(काष्ठा fb_cmap *cmap, पूर्णांक len, पूर्णांक transp, gfp_t flags)
अणु
	पूर्णांक size = len * माप(u16);
	पूर्णांक ret = -ENOMEM;

	flags |= __GFP_NOWARN;

	अगर (cmap->len != len) अणु
		fb_dealloc_cmap(cmap);
		अगर (!len)
			वापस 0;

		cmap->red = kzalloc(size, flags);
		अगर (!cmap->red)
			जाओ fail;
		cmap->green = kzalloc(size, flags);
		अगर (!cmap->green)
			जाओ fail;
		cmap->blue = kzalloc(size, flags);
		अगर (!cmap->blue)
			जाओ fail;
		अगर (transp) अणु
			cmap->transp = kzalloc(size, flags);
			अगर (!cmap->transp)
				जाओ fail;
		पूर्ण अन्यथा अणु
			cmap->transp = शून्य;
		पूर्ण
	पूर्ण
	cmap->start = 0;
	cmap->len = len;
	ret = fb_copy_cmap(fb_शेष_cmap(len), cmap);
	अगर (ret)
		जाओ fail;
	वापस 0;

fail:
	fb_dealloc_cmap(cmap);
	वापस ret;
पूर्ण

पूर्णांक fb_alloc_cmap(काष्ठा fb_cmap *cmap, पूर्णांक len, पूर्णांक transp)
अणु
	वापस fb_alloc_cmap_gfp(cmap, len, transp, GFP_ATOMIC);
पूर्ण

/**
 *      fb_dealloc_cmap - deallocate a colormap
 *      @cmap: frame buffer colormap काष्ठाure
 *
 *      Deallocates a colormap that was previously allocated with
 *      fb_alloc_cmap().
 *
 */

व्योम fb_dealloc_cmap(काष्ठा fb_cmap *cmap)
अणु
	kमुक्त(cmap->red);
	kमुक्त(cmap->green);
	kमुक्त(cmap->blue);
	kमुक्त(cmap->transp);

	cmap->red = cmap->green = cmap->blue = cmap->transp = शून्य;
	cmap->len = 0;
पूर्ण

/**
 *	fb_copy_cmap - copy a colormap
 *	@from: frame buffer colormap काष्ठाure
 *	@to: frame buffer colormap काष्ठाure
 *
 *	Copy contents of colormap from @from to @to.
 */

पूर्णांक fb_copy_cmap(स्थिर काष्ठा fb_cmap *from, काष्ठा fb_cmap *to)
अणु
	अचिन्हित पूर्णांक tooff = 0, fromoff = 0;
	माप_प्रकार size;

	अगर (to->start > from->start)
		fromoff = to->start - from->start;
	अन्यथा
		tooff = from->start - to->start;
	अगर (fromoff >= from->len || tooff >= to->len)
		वापस -EINVAL;

	size = min_t(माप_प्रकार, to->len - tooff, from->len - fromoff);
	अगर (size == 0)
		वापस -EINVAL;
	size *= माप(u16);

	स_नकल(to->red+tooff, from->red+fromoff, size);
	स_नकल(to->green+tooff, from->green+fromoff, size);
	स_नकल(to->blue+tooff, from->blue+fromoff, size);
	अगर (from->transp && to->transp)
		स_नकल(to->transp+tooff, from->transp+fromoff, size);
	वापस 0;
पूर्ण

पूर्णांक fb_cmap_to_user(स्थिर काष्ठा fb_cmap *from, काष्ठा fb_cmap_user *to)
अणु
	अचिन्हित पूर्णांक tooff = 0, fromoff = 0;
	माप_प्रकार size;

	अगर (to->start > from->start)
		fromoff = to->start - from->start;
	अन्यथा
		tooff = from->start - to->start;
	अगर (fromoff >= from->len || tooff >= to->len)
		वापस -EINVAL;

	size = min_t(माप_प्रकार, to->len - tooff, from->len - fromoff);
	अगर (size == 0)
		वापस -EINVAL;
	size *= माप(u16);

	अगर (copy_to_user(to->red+tooff, from->red+fromoff, size))
		वापस -EFAULT;
	अगर (copy_to_user(to->green+tooff, from->green+fromoff, size))
		वापस -EFAULT;
	अगर (copy_to_user(to->blue+tooff, from->blue+fromoff, size))
		वापस -EFAULT;
	अगर (from->transp && to->transp)
		अगर (copy_to_user(to->transp+tooff, from->transp+fromoff, size))
			वापस -EFAULT;
	वापस 0;
पूर्ण

/**
 *	fb_set_cmap - set the colormap
 *	@cmap: frame buffer colormap काष्ठाure
 *	@info: frame buffer info काष्ठाure
 *
 *	Sets the colormap @cmap क्रम a screen of device @info.
 *
 *	Returns negative त्रुटि_सं on error, or zero on success.
 *
 */

पूर्णांक fb_set_cmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info)
अणु
	पूर्णांक i, start, rc = 0;
	u16 *red, *green, *blue, *transp;
	u_पूर्णांक hred, hgreen, hblue, htransp = 0xffff;

	red = cmap->red;
	green = cmap->green;
	blue = cmap->blue;
	transp = cmap->transp;
	start = cmap->start;

	अगर (start < 0 || (!info->fbops->fb_setcolreg &&
			  !info->fbops->fb_setcmap))
		वापस -EINVAL;
	अगर (info->fbops->fb_setcmap) अणु
		rc = info->fbops->fb_setcmap(cmap, info);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < cmap->len; i++) अणु
			hred = *red++;
			hgreen = *green++;
			hblue = *blue++;
			अगर (transp)
				htransp = *transp++;
			अगर (info->fbops->fb_setcolreg(start++,
						      hred, hgreen, hblue,
						      htransp, info))
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (rc == 0)
		fb_copy_cmap(cmap, &info->cmap);

	वापस rc;
पूर्ण

पूर्णांक fb_set_user_cmap(काष्ठा fb_cmap_user *cmap, काष्ठा fb_info *info)
अणु
	पूर्णांक rc, size = cmap->len * माप(u16);
	काष्ठा fb_cmap umap;

	अगर (size < 0 || size < cmap->len)
		वापस -E2BIG;

	स_रखो(&umap, 0, माप(काष्ठा fb_cmap));
	rc = fb_alloc_cmap_gfp(&umap, cmap->len, cmap->transp != शून्य,
				GFP_KERNEL);
	अगर (rc)
		वापस rc;
	अगर (copy_from_user(umap.red, cmap->red, size) ||
	    copy_from_user(umap.green, cmap->green, size) ||
	    copy_from_user(umap.blue, cmap->blue, size) ||
	    (cmap->transp && copy_from_user(umap.transp, cmap->transp, size))) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	umap.start = cmap->start;
	lock_fb_info(info);
	rc = fb_set_cmap(&umap, info);
	unlock_fb_info(info);
out:
	fb_dealloc_cmap(&umap);
	वापस rc;
पूर्ण

/**
 *	fb_शेष_cmap - get शेष colormap
 *	@len: size of palette क्रम a depth
 *
 *	Gets the शेष colormap क्रम a specअगरic screen depth.  @len
 *	is the size of the palette क्रम a particular screen depth.
 *
 *	Returns poपूर्णांकer to a frame buffer colormap काष्ठाure.
 *
 */

स्थिर काष्ठा fb_cmap *fb_शेष_cmap(पूर्णांक len)
अणु
    अगर (len <= 2)
	वापस &शेष_2_colors;
    अगर (len <= 4)
	वापस &शेष_4_colors;
    अगर (len <= 8)
	वापस &शेष_8_colors;
    वापस &शेष_16_colors;
पूर्ण


/**
 *	fb_invert_cmaps - invert all शेषs colormaps
 *
 *	Invert all शेष colormaps.
 *
 */

व्योम fb_invert_cmaps(व्योम)
अणु
    u_पूर्णांक i;

    क्रम (i = 0; i < ARRAY_SIZE(red2); i++) अणु
	red2[i] = ~red2[i];
	green2[i] = ~green2[i];
	blue2[i] = ~blue2[i];
    पूर्ण
    क्रम (i = 0; i < ARRAY_SIZE(red4); i++) अणु
	red4[i] = ~red4[i];
	green4[i] = ~green4[i];
	blue4[i] = ~blue4[i];
    पूर्ण
    क्रम (i = 0; i < ARRAY_SIZE(red8); i++) अणु
	red8[i] = ~red8[i];
	green8[i] = ~green8[i];
	blue8[i] = ~blue8[i];
    पूर्ण
    क्रम (i = 0; i < ARRAY_SIZE(red16); i++) अणु
	red16[i] = ~red16[i];
	green16[i] = ~green16[i];
	blue16[i] = ~blue16[i];
    पूर्ण
पूर्ण


    /*
     *  Visible symbols क्रम modules
     */

EXPORT_SYMBOL(fb_alloc_cmap);
EXPORT_SYMBOL(fb_dealloc_cmap);
EXPORT_SYMBOL(fb_copy_cmap);
EXPORT_SYMBOL(fb_set_cmap);
EXPORT_SYMBOL(fb_शेष_cmap);
EXPORT_SYMBOL(fb_invert_cmaps);
