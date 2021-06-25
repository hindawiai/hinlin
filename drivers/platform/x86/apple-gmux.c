<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Gmux driver क्रम Apple laptops
 *
 *  Copyright (C) Canonical Ltd. <seth.क्रमshee@canonical.com>
 *  Copyright (C) 2010-2012 Andreas Heider <andreas@meetr.de>
 *  Copyright (C) 2015 Lukas Wunner <lukas@wunner.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/backlight.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pnp.h>
#समावेश <linux/apple_bl.h>
#समावेश <linux/apple-gmux.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <acpi/video.h>
#समावेश <यंत्र/पन.स>

/**
 * DOC: Overview
 *
 * gmux is a microcontroller built पूर्णांकo the MacBook Pro to support dual GPUs:
 * A `Lattice XP2`_ on pre-retinas, a `Renesas R4F2113`_ on retinas.
 *
 * (The MacPro6,1 2013 also has a gmux, however it is unclear why since it has
 * dual GPUs but no built-in display.)
 *
 * gmux is connected to the LPC bus of the southbridge. Its I/O ports are
 * accessed dअगरferently depending on the microcontroller: Driver functions
 * to access a pre-retina gmux are infixed ``_pio_``, those क्रम a retina gmux
 * are infixed ``_index_``.
 *
 * .. _Lattice XP2:
 *     http://www.latticesemi.com/en/Products/FPGAandCPLD/LatticeXP2.aspx
 * .. _Renesas R4F2113:
 *     http://www.renesas.com/products/mpumcu/h8s/h8s2100/h8s2113/index.jsp
 */

काष्ठा apple_gmux_data अणु
	अचिन्हित दीर्घ iostart;
	अचिन्हित दीर्घ iolen;
	bool indexed;
	काष्ठा mutex index_lock;

	काष्ठा backlight_device *bdev;

	/* चयनeroo data */
	acpi_handle dhandle;
	पूर्णांक gpe;
	bool बाह्यal_चयनable;
	क्रमागत vga_चयनeroo_client_id चयन_state_display;
	क्रमागत vga_चयनeroo_client_id चयन_state_ddc;
	क्रमागत vga_चयनeroo_client_id चयन_state_बाह्यal;
	क्रमागत vga_चयनeroo_state घातer_state;
	काष्ठा completion घातerchange_करोne;
पूर्ण;

अटल काष्ठा apple_gmux_data *apple_gmux_data;

/*
 * gmux port offsets. Many of these are not yet used, but may be in the
 * future, and it's useful to have them करोcumented here anyhow.
 */
#घोषणा GMUX_PORT_VERSION_MAJOR		0x04
#घोषणा GMUX_PORT_VERSION_MINOR		0x05
#घोषणा GMUX_PORT_VERSION_RELEASE	0x06
#घोषणा GMUX_PORT_SWITCH_DISPLAY	0x10
#घोषणा GMUX_PORT_SWITCH_GET_DISPLAY	0x11
#घोषणा GMUX_PORT_INTERRUPT_ENABLE	0x14
#घोषणा GMUX_PORT_INTERRUPT_STATUS	0x16
#घोषणा GMUX_PORT_SWITCH_DDC		0x28
#घोषणा GMUX_PORT_SWITCH_EXTERNAL	0x40
#घोषणा GMUX_PORT_SWITCH_GET_EXTERNAL	0x41
#घोषणा GMUX_PORT_DISCRETE_POWER	0x50
#घोषणा GMUX_PORT_MAX_BRIGHTNESS	0x70
#घोषणा GMUX_PORT_BRIGHTNESS		0x74
#घोषणा GMUX_PORT_VALUE			0xc2
#घोषणा GMUX_PORT_READ			0xd0
#घोषणा GMUX_PORT_WRITE			0xd4

#घोषणा GMUX_MIN_IO_LEN			(GMUX_PORT_BRIGHTNESS + 4)

#घोषणा GMUX_INTERRUPT_ENABLE		0xff
#घोषणा GMUX_INTERRUPT_DISABLE		0x00

#घोषणा GMUX_INTERRUPT_STATUS_ACTIVE	0
#घोषणा GMUX_INTERRUPT_STATUS_DISPLAY	(1 << 0)
#घोषणा GMUX_INTERRUPT_STATUS_POWER	(1 << 2)
#घोषणा GMUX_INTERRUPT_STATUS_HOTPLUG	(1 << 3)

#घोषणा GMUX_BRIGHTNESS_MASK		0x00ffffff
#घोषणा GMUX_MAX_BRIGHTNESS		GMUX_BRIGHTNESS_MASK

अटल u8 gmux_pio_पढ़ो8(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port)
अणु
	वापस inb(gmux_data->iostart + port);
पूर्ण

अटल व्योम gmux_pio_ग_लिखो8(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port,
			       u8 val)
अणु
	outb(val, gmux_data->iostart + port);
पूर्ण

अटल u32 gmux_pio_पढ़ो32(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port)
अणु
	वापस inl(gmux_data->iostart + port);
पूर्ण

अटल व्योम gmux_pio_ग_लिखो32(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port,
			     u32 val)
अणु
	पूर्णांक i;
	u8 पंचांगpval;

	क्रम (i = 0; i < 4; i++) अणु
		पंचांगpval = (val >> (i * 8)) & 0xff;
		outb(पंचांगpval, gmux_data->iostart + port + i);
	पूर्ण
पूर्ण

अटल पूर्णांक gmux_index_रुको_पढ़ोy(काष्ठा apple_gmux_data *gmux_data)
अणु
	पूर्णांक i = 200;
	u8 gwr = inb(gmux_data->iostart + GMUX_PORT_WRITE);

	जबतक (i && (gwr & 0x01)) अणु
		inb(gmux_data->iostart + GMUX_PORT_READ);
		gwr = inb(gmux_data->iostart + GMUX_PORT_WRITE);
		udelay(100);
		i--;
	पूर्ण

	वापस !!i;
पूर्ण

अटल पूर्णांक gmux_index_रुको_complete(काष्ठा apple_gmux_data *gmux_data)
अणु
	पूर्णांक i = 200;
	u8 gwr = inb(gmux_data->iostart + GMUX_PORT_WRITE);

	जबतक (i && !(gwr & 0x01)) अणु
		gwr = inb(gmux_data->iostart + GMUX_PORT_WRITE);
		udelay(100);
		i--;
	पूर्ण

	अगर (gwr & 0x01)
		inb(gmux_data->iostart + GMUX_PORT_READ);

	वापस !!i;
पूर्ण

अटल u8 gmux_index_पढ़ो8(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port)
अणु
	u8 val;

	mutex_lock(&gmux_data->index_lock);
	gmux_index_रुको_पढ़ोy(gmux_data);
	outb((port & 0xff), gmux_data->iostart + GMUX_PORT_READ);
	gmux_index_रुको_complete(gmux_data);
	val = inb(gmux_data->iostart + GMUX_PORT_VALUE);
	mutex_unlock(&gmux_data->index_lock);

	वापस val;
पूर्ण

अटल व्योम gmux_index_ग_लिखो8(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port,
			      u8 val)
अणु
	mutex_lock(&gmux_data->index_lock);
	outb(val, gmux_data->iostart + GMUX_PORT_VALUE);
	gmux_index_रुको_पढ़ोy(gmux_data);
	outb(port & 0xff, gmux_data->iostart + GMUX_PORT_WRITE);
	gmux_index_रुको_complete(gmux_data);
	mutex_unlock(&gmux_data->index_lock);
पूर्ण

अटल u32 gmux_index_पढ़ो32(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port)
अणु
	u32 val;

	mutex_lock(&gmux_data->index_lock);
	gmux_index_रुको_पढ़ोy(gmux_data);
	outb((port & 0xff), gmux_data->iostart + GMUX_PORT_READ);
	gmux_index_रुको_complete(gmux_data);
	val = inl(gmux_data->iostart + GMUX_PORT_VALUE);
	mutex_unlock(&gmux_data->index_lock);

	वापस val;
पूर्ण

अटल व्योम gmux_index_ग_लिखो32(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port,
			       u32 val)
अणु
	पूर्णांक i;
	u8 पंचांगpval;

	mutex_lock(&gmux_data->index_lock);

	क्रम (i = 0; i < 4; i++) अणु
		पंचांगpval = (val >> (i * 8)) & 0xff;
		outb(पंचांगpval, gmux_data->iostart + GMUX_PORT_VALUE + i);
	पूर्ण

	gmux_index_रुको_पढ़ोy(gmux_data);
	outb(port & 0xff, gmux_data->iostart + GMUX_PORT_WRITE);
	gmux_index_रुको_complete(gmux_data);
	mutex_unlock(&gmux_data->index_lock);
पूर्ण

अटल u8 gmux_पढ़ो8(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port)
अणु
	अगर (gmux_data->indexed)
		वापस gmux_index_पढ़ो8(gmux_data, port);
	अन्यथा
		वापस gmux_pio_पढ़ो8(gmux_data, port);
पूर्ण

अटल व्योम gmux_ग_लिखो8(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port, u8 val)
अणु
	अगर (gmux_data->indexed)
		gmux_index_ग_लिखो8(gmux_data, port, val);
	अन्यथा
		gmux_pio_ग_लिखो8(gmux_data, port, val);
पूर्ण

अटल u32 gmux_पढ़ो32(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port)
अणु
	अगर (gmux_data->indexed)
		वापस gmux_index_पढ़ो32(gmux_data, port);
	अन्यथा
		वापस gmux_pio_पढ़ो32(gmux_data, port);
पूर्ण

अटल व्योम gmux_ग_लिखो32(काष्ठा apple_gmux_data *gmux_data, पूर्णांक port,
			     u32 val)
अणु
	अगर (gmux_data->indexed)
		gmux_index_ग_लिखो32(gmux_data, port, val);
	अन्यथा
		gmux_pio_ग_लिखो32(gmux_data, port, val);
पूर्ण

अटल bool gmux_is_indexed(काष्ठा apple_gmux_data *gmux_data)
अणु
	u16 val;

	outb(0xaa, gmux_data->iostart + 0xcc);
	outb(0x55, gmux_data->iostart + 0xcd);
	outb(0x00, gmux_data->iostart + 0xce);

	val = inb(gmux_data->iostart + 0xcc) |
		(inb(gmux_data->iostart + 0xcd) << 8);

	अगर (val == 0x55aa)
		वापस true;

	वापस false;
पूर्ण

/**
 * DOC: Backlight control
 *
 * On single GPU MacBooks, the PWM संकेत क्रम the backlight is generated by
 * the GPU. On dual GPU MacBook Pros by contrast, either GPU may be suspended
 * to conserve energy. Hence the PWM संकेत needs to be generated by a separate
 * backlight driver which is controlled by gmux. The earliest generation
 * MBP5 2008/09 uses a `TI LP8543`_ backlight driver. All newer models
 * use a `TI LP8545`_.
 *
 * .. _TI LP8543: https://www.ti.com/lit/ds/symlink/lp8543.pdf
 * .. _TI LP8545: https://www.ti.com/lit/ds/symlink/lp8545.pdf
 */

अटल पूर्णांक gmux_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा apple_gmux_data *gmux_data = bl_get_data(bd);
	वापस gmux_पढ़ो32(gmux_data, GMUX_PORT_BRIGHTNESS) &
	       GMUX_BRIGHTNESS_MASK;
पूर्ण

अटल पूर्णांक gmux_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा apple_gmux_data *gmux_data = bl_get_data(bd);
	u32 brightness = bd->props.brightness;

	अगर (bd->props.state & BL_CORE_SUSPENDED)
		वापस 0;

	gmux_ग_लिखो32(gmux_data, GMUX_PORT_BRIGHTNESS, brightness);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops gmux_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.get_brightness = gmux_get_brightness,
	.update_status = gmux_update_status,
पूर्ण;

/**
 * DOC: Graphics mux
 *
 * On pre-retinas, the LVDS outमाला_दो of both GPUs feed पूर्णांकo gmux which muxes
 * either of them to the panel. One of the tricks gmux has up its sleeve is
 * to lengthen the blanking पूर्णांकerval of its output during a चयन to
 * synchronize it with the GPU चयनed to. This allows क्रम a flicker-मुक्त
 * चयन that is imperceptible by the user (`US 8,687,007 B2`_).
 *
 * On retinas, muxing is no दीर्घer करोne by gmux itself, but by a separate
 * chip which is controlled by gmux. The chip is triple sourced, it is
 * either an `NXP CBTL06142`_, `TI HD3SS212`_ or `Pericom PI3VDP12412`_.
 * The panel is driven with eDP instead of LVDS since the pixel घड़ी
 * required क्रम retina resolution exceeds LVDS' limits.
 *
 * Pre-retinas are able to चयन the panel's DDC pins separately.
 * This is handled by a `TI SN74LV4066A`_ which is controlled by gmux.
 * The inactive GPU can thus probe the panel's EDID without चयनing over
 * the entire panel. Retinas lack this functionality as the chips used क्रम
 * eDP muxing are incapable of चयनing the AUX channel separately (see
 * the linked data sheets, Pericom would be capable but this is unused).
 * However the retina panel has the NO_AUX_HANDSHAKE_LINK_TRAINING bit set
 * in its DPCD, allowing the inactive GPU to skip the AUX handshake and
 * set up the output with link parameters pre-calibrated by the active GPU.
 *
 * The बाह्यal DP port is only fully चयनable on the first two unibody
 * MacBook Pro generations, MBP5 2008/09 and MBP6 2010. This is करोne by an
 * `NXP CBTL06141`_ which is controlled by gmux. It's the predecessor of the
 * eDP mux on retinas, the dअगरference being support क्रम 2.7 versus 5.4 Gbit/s.
 *
 * The following MacBook Pro generations replaced the बाह्यal DP port with a
 * combined DP/Thunderbolt port and lost the ability to चयन it between GPUs,
 * connecting it either to the discrete GPU or the Thunderbolt controller.
 * Oddly enough, जबतक the full port is no दीर्घer चयनable, AUX and HPD
 * are still चयनable by way of an `NXP CBTL03062`_ (on pre-retinas
 * MBP8 2011 and MBP9 2012) or two `TI TS3DS10224`_ (on retinas) under the
 * control of gmux. Since the पूर्णांकegrated GPU is missing the मुख्य link,
 * बाह्यal displays appear to it as phantoms which fail to link-train.
 *
 * gmux receives the HPD संकेत of all display connectors and sends an
 * पूर्णांकerrupt on hotplug. On generations which cannot चयन बाह्यal ports,
 * the discrete GPU can then be woken to drive the newly connected display.
 * The ability to चयन AUX on these generations could be used to improve
 * reliability of hotplug detection by having the पूर्णांकegrated GPU poll the
 * ports जबतक the discrete GPU is asleep, but currently we करो not make use
 * of this feature.
 *
 * Our चयनing policy क्रम the बाह्यal port is that on those generations
 * which are able to चयन it fully, the port is चयनed together with the
 * panel when IGD / DIS commands are issued to vga_चयनeroo. It is thus
 * possible to drive e.g. a beamer on battery घातer with the पूर्णांकegrated GPU.
 * The user may manually चयन to the discrete GPU अगर more perक्रमmance is
 * needed.
 *
 * On all newer generations, the बाह्यal port can only be driven by the
 * discrete GPU. If a display is plugged in जबतक the panel is चयनed to
 * the पूर्णांकegrated GPU, *both* GPUs will be in use क्रम maximum perक्रमmance.
 * To decrease घातer consumption, the user may manually चयन to the
 * discrete GPU, thereby suspending the पूर्णांकegrated GPU.
 *
 * gmux' initial चयन state on bootup is user configurable via the EFI
 * variable ``gpu-घातer-prefs-fa4ce28d-b62f-4c99-9cc3-6815686e30f9`` (5th byte,
 * 1 = IGD, 0 = DIS). Based on this setting, the EFI firmware tells gmux to
 * चयन the panel and the बाह्यal DP connector and allocates a framebuffer
 * क्रम the selected GPU.
 *
 * .. _US 8,687,007 B2: https://pimg-fpiw.uspto.gov/fdd/07/870/086/0.pdf
 * .. _NXP CBTL06141:   https://www.nxp.com/करोcuments/data_sheet/CBTL06141.pdf
 * .. _NXP CBTL06142:   https://www.nxp.com/करोcuments/data_sheet/CBTL06141.pdf
 * .. _TI HD3SS212:     https://www.ti.com/lit/ds/symlink/hd3ss212.pdf
 * .. _Pericom PI3VDP12412: https://www.pericom.com/assets/Datasheets/PI3VDP12412.pdf
 * .. _TI SN74LV4066A:  https://www.ti.com/lit/ds/symlink/sn74lv4066a.pdf
 * .. _NXP CBTL03062:   http://pdf.datasheetarchive.com/indexerfiles/Datasheets-SW16/DSASW00308511.pdf
 * .. _TI TS3DS10224:   https://www.ti.com/lit/ds/symlink/ts3ds10224.pdf
 */

अटल व्योम gmux_पढ़ो_चयन_state(काष्ठा apple_gmux_data *gmux_data)
अणु
	अगर (gmux_पढ़ो8(gmux_data, GMUX_PORT_SWITCH_DDC) == 1)
		gmux_data->चयन_state_ddc = VGA_SWITCHEROO_IGD;
	अन्यथा
		gmux_data->चयन_state_ddc = VGA_SWITCHEROO_DIS;

	अगर (gmux_पढ़ो8(gmux_data, GMUX_PORT_SWITCH_DISPLAY) == 2)
		gmux_data->चयन_state_display = VGA_SWITCHEROO_IGD;
	अन्यथा
		gmux_data->चयन_state_display = VGA_SWITCHEROO_DIS;

	अगर (gmux_पढ़ो8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL) == 2)
		gmux_data->चयन_state_बाह्यal = VGA_SWITCHEROO_IGD;
	अन्यथा
		gmux_data->चयन_state_बाह्यal = VGA_SWITCHEROO_DIS;
पूर्ण

अटल व्योम gmux_ग_लिखो_चयन_state(काष्ठा apple_gmux_data *gmux_data)
अणु
	अगर (gmux_data->चयन_state_ddc == VGA_SWITCHEROO_IGD)
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_DDC, 1);
	अन्यथा
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_DDC, 2);

	अगर (gmux_data->चयन_state_display == VGA_SWITCHEROO_IGD)
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_DISPLAY, 2);
	अन्यथा
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_DISPLAY, 3);

	अगर (gmux_data->चयन_state_बाह्यal == VGA_SWITCHEROO_IGD)
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL, 2);
	अन्यथा
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL, 3);
पूर्ण

अटल पूर्णांक gmux_चयनto(क्रमागत vga_चयनeroo_client_id id)
अणु
	apple_gmux_data->चयन_state_ddc = id;
	apple_gmux_data->चयन_state_display = id;
	अगर (apple_gmux_data->बाह्यal_चयनable)
		apple_gmux_data->चयन_state_बाह्यal = id;

	gmux_ग_लिखो_चयन_state(apple_gmux_data);

	वापस 0;
पूर्ण

अटल पूर्णांक gmux_चयन_ddc(क्रमागत vga_चयनeroo_client_id id)
अणु
	क्रमागत vga_चयनeroo_client_id old_ddc_owner =
		apple_gmux_data->चयन_state_ddc;

	अगर (id == old_ddc_owner)
		वापस id;

	pr_debug("Switching DDC from %d to %d\n", old_ddc_owner, id);
	apple_gmux_data->चयन_state_ddc = id;

	अगर (id == VGA_SWITCHEROO_IGD)
		gmux_ग_लिखो8(apple_gmux_data, GMUX_PORT_SWITCH_DDC, 1);
	अन्यथा
		gmux_ग_लिखो8(apple_gmux_data, GMUX_PORT_SWITCH_DDC, 2);

	वापस old_ddc_owner;
पूर्ण

/**
 * DOC: Power control
 *
 * gmux is able to cut घातer to the discrete GPU. It स्वतःmatically takes care
 * of the correct sequence to tear करोwn and bring up the घातer rails क्रम
 * core voltage, VRAM and PCIe.
 */

अटल पूर्णांक gmux_set_discrete_state(काष्ठा apple_gmux_data *gmux_data,
				   क्रमागत vga_चयनeroo_state state)
अणु
	reinit_completion(&gmux_data->घातerchange_करोne);

	अगर (state == VGA_SWITCHEROO_ON) अणु
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_DISCRETE_POWER, 1);
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_DISCRETE_POWER, 3);
		pr_debug("Discrete card powered up\n");
	पूर्ण अन्यथा अणु
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_DISCRETE_POWER, 1);
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_DISCRETE_POWER, 0);
		pr_debug("Discrete card powered down\n");
	पूर्ण

	gmux_data->घातer_state = state;

	अगर (gmux_data->gpe >= 0 &&
	    !रुको_क्रम_completion_पूर्णांकerruptible_समयout(&gmux_data->घातerchange_करोne,
						       msecs_to_jअगरfies(200)))
		pr_warn("Timeout waiting for gmux switch to complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक gmux_set_घातer_state(क्रमागत vga_चयनeroo_client_id id,
				क्रमागत vga_चयनeroo_state state)
अणु
	अगर (id == VGA_SWITCHEROO_IGD)
		वापस 0;

	वापस gmux_set_discrete_state(apple_gmux_data, state);
पूर्ण

अटल क्रमागत vga_चयनeroo_client_id gmux_get_client_id(काष्ठा pci_dev *pdev)
अणु
	/*
	 * Early Macbook Pros with चयनable graphics use nvidia
	 * पूर्णांकegrated graphics. Hardcode that the 9400M is पूर्णांकegrated.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL)
		वापस VGA_SWITCHEROO_IGD;
	अन्यथा अगर (pdev->venकरोr == PCI_VENDOR_ID_NVIDIA &&
		 pdev->device == 0x0863)
		वापस VGA_SWITCHEROO_IGD;
	अन्यथा
		वापस VGA_SWITCHEROO_DIS;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_handler gmux_handler_indexed = अणु
	.चयनto = gmux_चयनto,
	.घातer_state = gmux_set_घातer_state,
	.get_client_id = gmux_get_client_id,
पूर्ण;

अटल स्थिर काष्ठा vga_चयनeroo_handler gmux_handler_classic = अणु
	.चयनto = gmux_चयनto,
	.चयन_ddc = gmux_चयन_ddc,
	.घातer_state = gmux_set_घातer_state,
	.get_client_id = gmux_get_client_id,
पूर्ण;

/**
 * DOC: Interrupt
 *
 * gmux is also connected to a GPIO pin of the southbridge and thereby is able
 * to trigger an ACPI GPE. On the MBP5 2008/09 it's GPIO pin 22 of the Nvidia
 * MCP79, on all following generations it's GPIO pin 6 of the Intel PCH.
 * The GPE merely संकेतs that an पूर्णांकerrupt occurred, the actual type of event
 * is identअगरied by पढ़ोing a gmux रेजिस्टर.
 */

अटल अंतरभूत व्योम gmux_disable_पूर्णांकerrupts(काष्ठा apple_gmux_data *gmux_data)
अणु
	gmux_ग_लिखो8(gmux_data, GMUX_PORT_INTERRUPT_ENABLE,
		    GMUX_INTERRUPT_DISABLE);
पूर्ण

अटल अंतरभूत व्योम gmux_enable_पूर्णांकerrupts(काष्ठा apple_gmux_data *gmux_data)
अणु
	gmux_ग_लिखो8(gmux_data, GMUX_PORT_INTERRUPT_ENABLE,
		    GMUX_INTERRUPT_ENABLE);
पूर्ण

अटल अंतरभूत u8 gmux_पूर्णांकerrupt_get_status(काष्ठा apple_gmux_data *gmux_data)
अणु
	वापस gmux_पढ़ो8(gmux_data, GMUX_PORT_INTERRUPT_STATUS);
पूर्ण

अटल व्योम gmux_clear_पूर्णांकerrupts(काष्ठा apple_gmux_data *gmux_data)
अणु
	u8 status;

	/* to clear पूर्णांकerrupts ग_लिखो back current status */
	status = gmux_पूर्णांकerrupt_get_status(gmux_data);
	gmux_ग_लिखो8(gmux_data, GMUX_PORT_INTERRUPT_STATUS, status);
पूर्ण

अटल व्योम gmux_notअगरy_handler(acpi_handle device, u32 value, व्योम *context)
अणु
	u8 status;
	काष्ठा pnp_dev *pnp = (काष्ठा pnp_dev *)context;
	काष्ठा apple_gmux_data *gmux_data = pnp_get_drvdata(pnp);

	status = gmux_पूर्णांकerrupt_get_status(gmux_data);
	gmux_disable_पूर्णांकerrupts(gmux_data);
	pr_debug("Notify handler called: status %d\n", status);

	gmux_clear_पूर्णांकerrupts(gmux_data);
	gmux_enable_पूर्णांकerrupts(gmux_data);

	अगर (status & GMUX_INTERRUPT_STATUS_POWER)
		complete(&gmux_data->घातerchange_करोne);
पूर्ण

अटल पूर्णांक gmux_suspend(काष्ठा device *dev)
अणु
	काष्ठा pnp_dev *pnp = to_pnp_dev(dev);
	काष्ठा apple_gmux_data *gmux_data = pnp_get_drvdata(pnp);

	gmux_disable_पूर्णांकerrupts(gmux_data);
	वापस 0;
पूर्ण

अटल पूर्णांक gmux_resume(काष्ठा device *dev)
अणु
	काष्ठा pnp_dev *pnp = to_pnp_dev(dev);
	काष्ठा apple_gmux_data *gmux_data = pnp_get_drvdata(pnp);

	gmux_enable_पूर्णांकerrupts(gmux_data);
	gmux_ग_लिखो_चयन_state(gmux_data);
	अगर (gmux_data->घातer_state == VGA_SWITCHEROO_OFF)
		gmux_set_discrete_state(gmux_data, gmux_data->घातer_state);
	वापस 0;
पूर्ण

अटल पूर्णांक is_thunderbolt(काष्ठा device *dev, व्योम *data)
अणु
	वापस to_pci_dev(dev)->is_thunderbolt;
पूर्ण

अटल पूर्णांक gmux_probe(काष्ठा pnp_dev *pnp, स्थिर काष्ठा pnp_device_id *id)
अणु
	काष्ठा apple_gmux_data *gmux_data;
	काष्ठा resource *res;
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bdev;
	u8 ver_major, ver_minor, ver_release;
	पूर्णांक ret = -ENXIO;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ gpe;

	अगर (apple_gmux_data)
		वापस -EBUSY;

	gmux_data = kzalloc(माप(*gmux_data), GFP_KERNEL);
	अगर (!gmux_data)
		वापस -ENOMEM;
	pnp_set_drvdata(pnp, gmux_data);

	res = pnp_get_resource(pnp, IORESOURCE_IO, 0);
	अगर (!res) अणु
		pr_err("Failed to find gmux I/O resource\n");
		जाओ err_मुक्त;
	पूर्ण

	gmux_data->iostart = res->start;
	gmux_data->iolen = res->end - res->start;

	अगर (gmux_data->iolen < GMUX_MIN_IO_LEN) अणु
		pr_err("gmux I/O region too small (%lu < %u)\n",
		       gmux_data->iolen, GMUX_MIN_IO_LEN);
		जाओ err_मुक्त;
	पूर्ण

	अगर (!request_region(gmux_data->iostart, gmux_data->iolen,
			    "Apple gmux")) अणु
		pr_err("gmux I/O already in use\n");
		जाओ err_मुक्त;
	पूर्ण

	/*
	 * Invalid version inक्रमmation may indicate either that the gmux
	 * device isn't present or that it's a new one that uses indexed
	 * io
	 */

	ver_major = gmux_पढ़ो8(gmux_data, GMUX_PORT_VERSION_MAJOR);
	ver_minor = gmux_पढ़ो8(gmux_data, GMUX_PORT_VERSION_MINOR);
	ver_release = gmux_पढ़ो8(gmux_data, GMUX_PORT_VERSION_RELEASE);
	अगर (ver_major == 0xff && ver_minor == 0xff && ver_release == 0xff) अणु
		अगर (gmux_is_indexed(gmux_data)) अणु
			u32 version;
			mutex_init(&gmux_data->index_lock);
			gmux_data->indexed = true;
			version = gmux_पढ़ो32(gmux_data,
				GMUX_PORT_VERSION_MAJOR);
			ver_major = (version >> 24) & 0xff;
			ver_minor = (version >> 16) & 0xff;
			ver_release = (version >> 8) & 0xff;
		पूर्ण अन्यथा अणु
			pr_info("gmux device not present\n");
			ret = -ENODEV;
			जाओ err_release;
		पूर्ण
	पूर्ण
	pr_info("Found gmux version %d.%d.%d [%s]\n", ver_major, ver_minor,
		ver_release, (gmux_data->indexed ? "indexed" : "classic"));

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = gmux_पढ़ो32(gmux_data, GMUX_PORT_MAX_BRIGHTNESS);

	/*
	 * Currently it's assumed that the maximum brightness is less than
	 * 2^24 क्रम compatibility with old gmux versions. Cap the max
	 * brightness at this value, but prपूर्णांक a warning अगर the hardware
	 * reports something higher so that it can be fixed.
	 */
	अगर (WARN_ON(props.max_brightness > GMUX_MAX_BRIGHTNESS))
		props.max_brightness = GMUX_MAX_BRIGHTNESS;

	bdev = backlight_device_रेजिस्टर("gmux_backlight", &pnp->dev,
					 gmux_data, &gmux_bl_ops, &props);
	अगर (IS_ERR(bdev)) अणु
		ret = PTR_ERR(bdev);
		जाओ err_release;
	पूर्ण

	gmux_data->bdev = bdev;
	bdev->props.brightness = gmux_get_brightness(bdev);
	backlight_update_status(bdev);

	/*
	 * The backlight situation on Macs is complicated. If the gmux is
	 * present it's the best choice, because it always works क्रम
	 * backlight control and supports more levels than other options.
	 * Disable the other backlight choices.
	 */
	acpi_video_set_dmi_backlight_type(acpi_backlight_venकरोr);
	apple_bl_unरेजिस्टर();

	gmux_data->घातer_state = VGA_SWITCHEROO_ON;

	gmux_data->dhandle = ACPI_HANDLE(&pnp->dev);
	अगर (!gmux_data->dhandle) अणु
		pr_err("Cannot find acpi handle for pnp device %s\n",
		       dev_name(&pnp->dev));
		ret = -ENODEV;
		जाओ err_notअगरy;
	पूर्ण

	status = acpi_evaluate_पूर्णांकeger(gmux_data->dhandle, "GMGP", शून्य, &gpe);
	अगर (ACPI_SUCCESS(status)) अणु
		gmux_data->gpe = (पूर्णांक)gpe;

		status = acpi_install_notअगरy_handler(gmux_data->dhandle,
						     ACPI_DEVICE_NOTIFY,
						     &gmux_notअगरy_handler, pnp);
		अगर (ACPI_FAILURE(status)) अणु
			pr_err("Install notify handler failed: %s\n",
			       acpi_क्रमmat_exception(status));
			ret = -ENODEV;
			जाओ err_notअगरy;
		पूर्ण

		status = acpi_enable_gpe(शून्य, gmux_data->gpe);
		अगर (ACPI_FAILURE(status)) अणु
			pr_err("Cannot enable gpe: %s\n",
			       acpi_क्रमmat_exception(status));
			जाओ err_enable_gpe;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("No GPE found for gmux\n");
		gmux_data->gpe = -1;
	पूर्ण

	/*
	 * If Thunderbolt is present, the बाह्यal DP port is not fully
	 * चयनable. Force its AUX channel to the discrete GPU.
	 */
	gmux_data->बाह्यal_चयनable =
		!bus_क्रम_each_dev(&pci_bus_type, शून्य, शून्य, is_thunderbolt);
	अगर (!gmux_data->बाह्यal_चयनable)
		gmux_ग_लिखो8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL, 3);

	apple_gmux_data = gmux_data;
	init_completion(&gmux_data->घातerchange_करोne);
	gmux_enable_पूर्णांकerrupts(gmux_data);
	gmux_पढ़ो_चयन_state(gmux_data);

	/*
	 * Retina MacBook Pros cannot चयन the panel's AUX separately
	 * and need eDP pre-calibration. They are distinguishable from
	 * pre-retinas by having an "indexed" gmux.
	 *
	 * Pre-retina MacBook Pros can चयन the panel's DDC separately.
	 */
	अगर (gmux_data->indexed)
		ret = vga_चयनeroo_रेजिस्टर_handler(&gmux_handler_indexed,
					      VGA_SWITCHEROO_NEEDS_EDP_CONFIG);
	अन्यथा
		ret = vga_चयनeroo_रेजिस्टर_handler(&gmux_handler_classic,
					      VGA_SWITCHEROO_CAN_SWITCH_DDC);
	अगर (ret) अणु
		pr_err("Failed to register vga_switcheroo handler\n");
		जाओ err_रेजिस्टर_handler;
	पूर्ण

	वापस 0;

err_रेजिस्टर_handler:
	gmux_disable_पूर्णांकerrupts(gmux_data);
	apple_gmux_data = शून्य;
	अगर (gmux_data->gpe >= 0)
		acpi_disable_gpe(शून्य, gmux_data->gpe);
err_enable_gpe:
	अगर (gmux_data->gpe >= 0)
		acpi_हटाओ_notअगरy_handler(gmux_data->dhandle,
					   ACPI_DEVICE_NOTIFY,
					   &gmux_notअगरy_handler);
err_notअगरy:
	backlight_device_unरेजिस्टर(bdev);
err_release:
	release_region(gmux_data->iostart, gmux_data->iolen);
err_मुक्त:
	kमुक्त(gmux_data);
	वापस ret;
पूर्ण

अटल व्योम gmux_हटाओ(काष्ठा pnp_dev *pnp)
अणु
	काष्ठा apple_gmux_data *gmux_data = pnp_get_drvdata(pnp);

	vga_चयनeroo_unरेजिस्टर_handler();
	gmux_disable_पूर्णांकerrupts(gmux_data);
	अगर (gmux_data->gpe >= 0) अणु
		acpi_disable_gpe(शून्य, gmux_data->gpe);
		acpi_हटाओ_notअगरy_handler(gmux_data->dhandle,
					   ACPI_DEVICE_NOTIFY,
					   &gmux_notअगरy_handler);
	पूर्ण

	backlight_device_unरेजिस्टर(gmux_data->bdev);

	release_region(gmux_data->iostart, gmux_data->iolen);
	apple_gmux_data = शून्य;
	kमुक्त(gmux_data);

	acpi_video_रेजिस्टर();
	apple_bl_रेजिस्टर();
पूर्ण

अटल स्थिर काष्ठा pnp_device_id gmux_device_ids[] = अणु
	अणुGMUX_ACPI_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops gmux_dev_pm_ops = अणु
	.suspend = gmux_suspend,
	.resume = gmux_resume,
पूर्ण;

अटल काष्ठा pnp_driver gmux_pnp_driver = अणु
	.name		= "apple-gmux",
	.probe		= gmux_probe,
	.हटाओ		= gmux_हटाओ,
	.id_table	= gmux_device_ids,
	.driver		= अणु
			.pm = &gmux_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_pnp_driver(gmux_pnp_driver);
MODULE_AUTHOR("Seth Forshee <seth.forshee@canonical.com>");
MODULE_DESCRIPTION("Apple Gmux Driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pnp, gmux_device_ids);
