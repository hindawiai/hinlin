<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* -----------------------------------------------------------------------
 *
 *   Copyright 2011 Intel Corporation; author Matt Fleming
 *
 * ----------------------------------------------------------------------- */

#समावेश <linux/bitops.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/efi.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/setup.h>

#समावेश "efistub.h"

क्रमागत efi_cmdline_option अणु
	EFI_CMDLINE_NONE,
	EFI_CMDLINE_MODE_NUM,
	EFI_CMDLINE_RES,
	EFI_CMDLINE_AUTO,
	EFI_CMDLINE_LIST
पूर्ण;

अटल काष्ठा अणु
	क्रमागत efi_cmdline_option option;
	जोड़ अणु
		u32 mode;
		काष्ठा अणु
			u32 width, height;
			पूर्णांक क्रमmat;
			u8 depth;
		पूर्ण res;
	पूर्ण;
पूर्ण cmdline = अणु .option = EFI_CMDLINE_NONE पूर्ण;

अटल bool parse_modक्रमागत(अक्षर *option, अक्षर **next)
अणु
	u32 m;

	अगर (!strstarts(option, "mode="))
		वापस false;
	option += म_माप("mode=");
	m = simple_म_से_अदीर्घl(option, &option, 0);
	अगर (*option && *option++ != ',')
		वापस false;
	cmdline.option = EFI_CMDLINE_MODE_NUM;
	cmdline.mode   = m;

	*next = option;
	वापस true;
पूर्ण

अटल bool parse_res(अक्षर *option, अक्षर **next)
अणु
	u32 w, h, d = 0;
	पूर्णांक pf = -1;

	अगर (!है_अंक(*option))
		वापस false;
	w = simple_म_से_अदीर्घl(option, &option, 10);
	अगर (*option++ != 'x' || !है_अंक(*option))
		वापस false;
	h = simple_म_से_अदीर्घl(option, &option, 10);
	अगर (*option == '-') अणु
		option++;
		अगर (strstarts(option, "rgb")) अणु
			option += म_माप("rgb");
			pf = PIXEL_RGB_RESERVED_8BIT_PER_COLOR;
		पूर्ण अन्यथा अगर (strstarts(option, "bgr")) अणु
			option += म_माप("bgr");
			pf = PIXEL_BGR_RESERVED_8BIT_PER_COLOR;
		पूर्ण अन्यथा अगर (है_अंक(*option))
			d = simple_म_से_अदीर्घl(option, &option, 10);
		अन्यथा
			वापस false;
	पूर्ण
	अगर (*option && *option++ != ',')
		वापस false;
	cmdline.option     = EFI_CMDLINE_RES;
	cmdline.res.width  = w;
	cmdline.res.height = h;
	cmdline.res.क्रमmat = pf;
	cmdline.res.depth  = d;

	*next = option;
	वापस true;
पूर्ण

अटल bool parse_स्वतः(अक्षर *option, अक्षर **next)
अणु
	अगर (!strstarts(option, "auto"))
		वापस false;
	option += म_माप("auto");
	अगर (*option && *option++ != ',')
		वापस false;
	cmdline.option = EFI_CMDLINE_AUTO;

	*next = option;
	वापस true;
पूर्ण

अटल bool parse_list(अक्षर *option, अक्षर **next)
अणु
	अगर (!strstarts(option, "list"))
		वापस false;
	option += म_माप("list");
	अगर (*option && *option++ != ',')
		वापस false;
	cmdline.option = EFI_CMDLINE_LIST;

	*next = option;
	वापस true;
पूर्ण

व्योम efi_parse_option_graphics(अक्षर *option)
अणु
	जबतक (*option) अणु
		अगर (parse_modक्रमागत(option, &option))
			जारी;
		अगर (parse_res(option, &option))
			जारी;
		अगर (parse_स्वतः(option, &option))
			जारी;
		अगर (parse_list(option, &option))
			जारी;

		जबतक (*option && *option++ != ',')
			;
	पूर्ण
पूर्ण

अटल u32 choose_mode_modक्रमागत(efi_graphics_output_protocol_t *gop)
अणु
	efi_status_t status;

	efi_graphics_output_protocol_mode_t *mode;
	efi_graphics_output_mode_info_t *info;
	अचिन्हित दीर्घ info_size;

	u32 max_mode, cur_mode;
	पूर्णांक pf;

	mode = efi_table_attr(gop, mode);

	cur_mode = efi_table_attr(mode, mode);
	अगर (cmdline.mode == cur_mode)
		वापस cur_mode;

	max_mode = efi_table_attr(mode, max_mode);
	अगर (cmdline.mode >= max_mode) अणु
		efi_err("Requested mode is invalid\n");
		वापस cur_mode;
	पूर्ण

	status = efi_call_proto(gop, query_mode, cmdline.mode,
				&info_size, &info);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Couldn't get mode information\n");
		वापस cur_mode;
	पूर्ण

	pf = info->pixel_क्रमmat;

	efi_bs_call(मुक्त_pool, info);

	अगर (pf == PIXEL_BLT_ONLY || pf >= PIXEL_FORMAT_MAX) अणु
		efi_err("Invalid PixelFormat\n");
		वापस cur_mode;
	पूर्ण

	वापस cmdline.mode;
पूर्ण

अटल u8 pixel_bpp(पूर्णांक pixel_क्रमmat, efi_pixel_biपंचांगask_t pixel_info)
अणु
	अगर (pixel_क्रमmat == PIXEL_BIT_MASK) अणु
		u32 mask = pixel_info.red_mask | pixel_info.green_mask |
			   pixel_info.blue_mask | pixel_info.reserved_mask;
		अगर (!mask)
			वापस 0;
		वापस __fls(mask) - __ffs(mask) + 1;
	पूर्ण अन्यथा
		वापस 32;
पूर्ण

अटल u32 choose_mode_res(efi_graphics_output_protocol_t *gop)
अणु
	efi_status_t status;

	efi_graphics_output_protocol_mode_t *mode;
	efi_graphics_output_mode_info_t *info;
	अचिन्हित दीर्घ info_size;

	u32 max_mode, cur_mode;
	पूर्णांक pf;
	efi_pixel_biपंचांगask_t pi;
	u32 m, w, h;

	mode = efi_table_attr(gop, mode);

	cur_mode = efi_table_attr(mode, mode);
	info = efi_table_attr(mode, info);
	pf = info->pixel_क्रमmat;
	pi = info->pixel_inक्रमmation;
	w  = info->horizontal_resolution;
	h  = info->vertical_resolution;

	अगर (w == cmdline.res.width && h == cmdline.res.height &&
	    (cmdline.res.क्रमmat < 0 || cmdline.res.क्रमmat == pf) &&
	    (!cmdline.res.depth || cmdline.res.depth == pixel_bpp(pf, pi)))
		वापस cur_mode;

	max_mode = efi_table_attr(mode, max_mode);

	क्रम (m = 0; m < max_mode; m++) अणु
		अगर (m == cur_mode)
			जारी;

		status = efi_call_proto(gop, query_mode, m,
					&info_size, &info);
		अगर (status != EFI_SUCCESS)
			जारी;

		pf = info->pixel_क्रमmat;
		pi = info->pixel_inक्रमmation;
		w  = info->horizontal_resolution;
		h  = info->vertical_resolution;

		efi_bs_call(मुक्त_pool, info);

		अगर (pf == PIXEL_BLT_ONLY || pf >= PIXEL_FORMAT_MAX)
			जारी;
		अगर (w == cmdline.res.width && h == cmdline.res.height &&
		    (cmdline.res.क्रमmat < 0 || cmdline.res.क्रमmat == pf) &&
		    (!cmdline.res.depth || cmdline.res.depth == pixel_bpp(pf, pi)))
			वापस m;
	पूर्ण

	efi_err("Couldn't find requested mode\n");

	वापस cur_mode;
पूर्ण

अटल u32 choose_mode_स्वतः(efi_graphics_output_protocol_t *gop)
अणु
	efi_status_t status;

	efi_graphics_output_protocol_mode_t *mode;
	efi_graphics_output_mode_info_t *info;
	अचिन्हित दीर्घ info_size;

	u32 max_mode, cur_mode, best_mode, area;
	u8 depth;
	पूर्णांक pf;
	efi_pixel_biपंचांगask_t pi;
	u32 m, w, h, a;
	u8 d;

	mode = efi_table_attr(gop, mode);

	cur_mode = efi_table_attr(mode, mode);
	max_mode = efi_table_attr(mode, max_mode);

	info = efi_table_attr(mode, info);

	pf = info->pixel_क्रमmat;
	pi = info->pixel_inक्रमmation;
	w  = info->horizontal_resolution;
	h  = info->vertical_resolution;

	best_mode = cur_mode;
	area = w * h;
	depth = pixel_bpp(pf, pi);

	क्रम (m = 0; m < max_mode; m++) अणु
		अगर (m == cur_mode)
			जारी;

		status = efi_call_proto(gop, query_mode, m,
					&info_size, &info);
		अगर (status != EFI_SUCCESS)
			जारी;

		pf = info->pixel_क्रमmat;
		pi = info->pixel_inक्रमmation;
		w  = info->horizontal_resolution;
		h  = info->vertical_resolution;

		efi_bs_call(मुक्त_pool, info);

		अगर (pf == PIXEL_BLT_ONLY || pf >= PIXEL_FORMAT_MAX)
			जारी;
		a = w * h;
		अगर (a < area)
			जारी;
		d = pixel_bpp(pf, pi);
		अगर (a > area || d > depth) अणु
			best_mode = m;
			area = a;
			depth = d;
		पूर्ण
	पूर्ण

	वापस best_mode;
पूर्ण

अटल u32 choose_mode_list(efi_graphics_output_protocol_t *gop)
अणु
	efi_status_t status;

	efi_graphics_output_protocol_mode_t *mode;
	efi_graphics_output_mode_info_t *info;
	अचिन्हित दीर्घ info_size;

	u32 max_mode, cur_mode;
	पूर्णांक pf;
	efi_pixel_biपंचांगask_t pi;
	u32 m, w, h;
	u8 d;
	स्थिर अक्षर *dstr;
	bool valid;
	efi_input_key_t key;

	mode = efi_table_attr(gop, mode);

	cur_mode = efi_table_attr(mode, mode);
	max_mode = efi_table_attr(mode, max_mode);

	efi_prपूर्णांकk("Available graphics modes are 0-%u\n", max_mode-1);
	efi_माला_दो("  * = current mode\n"
		 "  - = unusable mode\n");
	क्रम (m = 0; m < max_mode; m++) अणु
		status = efi_call_proto(gop, query_mode, m,
					&info_size, &info);
		अगर (status != EFI_SUCCESS)
			जारी;

		pf = info->pixel_क्रमmat;
		pi = info->pixel_inक्रमmation;
		w  = info->horizontal_resolution;
		h  = info->vertical_resolution;

		efi_bs_call(मुक्त_pool, info);

		valid = !(pf == PIXEL_BLT_ONLY || pf >= PIXEL_FORMAT_MAX);
		d = 0;
		चयन (pf) अणु
		हाल PIXEL_RGB_RESERVED_8BIT_PER_COLOR:
			dstr = "rgb";
			अवरोध;
		हाल PIXEL_BGR_RESERVED_8BIT_PER_COLOR:
			dstr = "bgr";
			अवरोध;
		हाल PIXEL_BIT_MASK:
			dstr = "";
			d = pixel_bpp(pf, pi);
			अवरोध;
		हाल PIXEL_BLT_ONLY:
			dstr = "blt";
			अवरोध;
		शेष:
			dstr = "xxx";
			अवरोध;
		पूर्ण

		efi_prपूर्णांकk("Mode %3u %c%c: Resolution %ux%u-%s%.0hhu\n",
			   m,
			   m == cur_mode ? '*' : ' ',
			   !valid ? '-' : ' ',
			   w, h, dstr, d);
	पूर्ण

	efi_माला_दो("\nPress any key to continue (or wait 10 seconds)\n");
	status = efi_रुको_क्रम_key(10 * EFI_USEC_PER_SEC, &key);
	अगर (status != EFI_SUCCESS && status != EFI_TIMEOUT) अणु
		efi_err("Unable to read key, continuing in 10 seconds\n");
		efi_bs_call(stall, 10 * EFI_USEC_PER_SEC);
	पूर्ण

	वापस cur_mode;
पूर्ण

अटल व्योम set_mode(efi_graphics_output_protocol_t *gop)
अणु
	efi_graphics_output_protocol_mode_t *mode;
	u32 cur_mode, new_mode;

	चयन (cmdline.option) अणु
	हाल EFI_CMDLINE_MODE_NUM:
		new_mode = choose_mode_modक्रमागत(gop);
		अवरोध;
	हाल EFI_CMDLINE_RES:
		new_mode = choose_mode_res(gop);
		अवरोध;
	हाल EFI_CMDLINE_AUTO:
		new_mode = choose_mode_स्वतः(gop);
		अवरोध;
	हाल EFI_CMDLINE_LIST:
		new_mode = choose_mode_list(gop);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	mode = efi_table_attr(gop, mode);
	cur_mode = efi_table_attr(mode, mode);

	अगर (new_mode == cur_mode)
		वापस;

	अगर (efi_call_proto(gop, set_mode, new_mode) != EFI_SUCCESS)
		efi_err("Failed to set requested mode\n");
पूर्ण

अटल व्योम find_bits(u32 mask, u8 *pos, u8 *size)
अणु
	अगर (!mask) अणु
		*pos = *size = 0;
		वापस;
	पूर्ण

	/* UEFI spec guarantees that the set bits are contiguous */
	*pos  = __ffs(mask);
	*size = __fls(mask) - *pos + 1;
पूर्ण

अटल व्योम
setup_pixel_info(काष्ठा screen_info *si, u32 pixels_per_scan_line,
		 efi_pixel_biपंचांगask_t pixel_info, पूर्णांक pixel_क्रमmat)
अणु
	अगर (pixel_क्रमmat == PIXEL_BIT_MASK) अणु
		find_bits(pixel_info.red_mask,
			  &si->red_pos, &si->red_size);
		find_bits(pixel_info.green_mask,
			  &si->green_pos, &si->green_size);
		find_bits(pixel_info.blue_mask,
			  &si->blue_pos, &si->blue_size);
		find_bits(pixel_info.reserved_mask,
			  &si->rsvd_pos, &si->rsvd_size);
		si->lfb_depth = si->red_size + si->green_size +
			si->blue_size + si->rsvd_size;
		si->lfb_linelength = (pixels_per_scan_line * si->lfb_depth) / 8;
	पूर्ण अन्यथा अणु
		अगर (pixel_क्रमmat == PIXEL_RGB_RESERVED_8BIT_PER_COLOR) अणु
			si->red_pos   = 0;
			si->blue_pos  = 16;
		पूर्ण अन्यथा /* PIXEL_BGR_RESERVED_8BIT_PER_COLOR */ अणु
			si->blue_pos  = 0;
			si->red_pos   = 16;
		पूर्ण

		si->green_pos = 8;
		si->rsvd_pos  = 24;
		si->red_size = si->green_size =
			si->blue_size = si->rsvd_size = 8;

		si->lfb_depth = 32;
		si->lfb_linelength = pixels_per_scan_line * 4;
	पूर्ण
पूर्ण

अटल efi_graphics_output_protocol_t *
find_gop(efi_guid_t *proto, अचिन्हित दीर्घ size, व्योम **handles)
अणु
	efi_graphics_output_protocol_t *first_gop;
	efi_handle_t h;
	पूर्णांक i;

	first_gop = शून्य;

	क्रम_each_efi_handle(h, handles, size, i) अणु
		efi_status_t status;

		efi_graphics_output_protocol_t *gop;
		efi_graphics_output_protocol_mode_t *mode;
		efi_graphics_output_mode_info_t *info;

		efi_guid_t conout_proto = EFI_CONSOLE_OUT_DEVICE_GUID;
		व्योम *dummy = शून्य;

		status = efi_bs_call(handle_protocol, h, proto, (व्योम **)&gop);
		अगर (status != EFI_SUCCESS)
			जारी;

		mode = efi_table_attr(gop, mode);
		info = efi_table_attr(mode, info);
		अगर (info->pixel_क्रमmat == PIXEL_BLT_ONLY ||
		    info->pixel_क्रमmat >= PIXEL_FORMAT_MAX)
			जारी;

		/*
		 * Systems that use the UEFI Console Splitter may
		 * provide multiple GOP devices, not all of which are
		 * backed by real hardware. The workaround is to search
		 * क्रम a GOP implementing the ConOut protocol, and अगर
		 * one isn't found, to just fall back to the first GOP.
		 *
		 * Once we've found a GOP supporting ConOut,
		 * करोn't bother looking any further.
		 */
		status = efi_bs_call(handle_protocol, h, &conout_proto, &dummy);
		अगर (status == EFI_SUCCESS)
			वापस gop;

		अगर (!first_gop)
			first_gop = gop;
	पूर्ण

	वापस first_gop;
पूर्ण

अटल efi_status_t setup_gop(काष्ठा screen_info *si, efi_guid_t *proto,
			      अचिन्हित दीर्घ size, व्योम **handles)
अणु
	efi_graphics_output_protocol_t *gop;
	efi_graphics_output_protocol_mode_t *mode;
	efi_graphics_output_mode_info_t *info;

	gop = find_gop(proto, size, handles);

	/* Did we find any GOPs? */
	अगर (!gop)
		वापस EFI_NOT_FOUND;

	/* Change mode अगर requested */
	set_mode(gop);

	/* EFI framebuffer */
	mode = efi_table_attr(gop, mode);
	info = efi_table_attr(mode, info);

	si->orig_video_isVGA = VIDEO_TYPE_EFI;

	si->lfb_width  = info->horizontal_resolution;
	si->lfb_height = info->vertical_resolution;

	efi_set_u64_split(efi_table_attr(mode, frame_buffer_base),
			  &si->lfb_base, &si->ext_lfb_base);
	अगर (si->ext_lfb_base)
		si->capabilities |= VIDEO_CAPABILITY_64BIT_BASE;

	si->pages = 1;

	setup_pixel_info(si, info->pixels_per_scan_line,
			     info->pixel_inक्रमmation, info->pixel_क्रमmat);

	si->lfb_size = si->lfb_linelength * si->lfb_height;

	si->capabilities |= VIDEO_CAPABILITY_SKIP_QUIRKS;

	वापस EFI_SUCCESS;
पूर्ण

/*
 * See अगर we have Graphics Output Protocol
 */
efi_status_t efi_setup_gop(काष्ठा screen_info *si, efi_guid_t *proto,
			   अचिन्हित दीर्घ size)
अणु
	efi_status_t status;
	व्योम **gop_handle = शून्य;

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, size,
			     (व्योम **)&gop_handle);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL, proto, शून्य,
			     &size, gop_handle);
	अगर (status != EFI_SUCCESS)
		जाओ मुक्त_handle;

	status = setup_gop(si, proto, size, gop_handle);

मुक्त_handle:
	efi_bs_call(मुक्त_pool, gop_handle);
	वापस status;
पूर्ण
