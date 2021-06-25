<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel ACPI functions
 *
 * _DSM related code stolen from nouveau_acpi.c.
 */

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>

#समावेश "i915_drv.h"
#समावेश "intel_acpi.h"
#समावेश "intel_display_types.h"

#घोषणा INTEL_DSM_REVISION_ID 1 /* For Calpella anyway... */
#घोषणा INTEL_DSM_FN_PLATFORM_MUX_INFO 1 /* No args */

अटल स्थिर guid_t पूर्णांकel_dsm_guid =
	GUID_INIT(0x7ed873d3, 0xc2d0, 0x4e4f,
		  0xa8, 0x54, 0x0f, 0x13, 0x17, 0xb0, 0x1c, 0x2c);

अटल अक्षर *पूर्णांकel_dsm_port_name(u8 id)
अणु
	चयन (id) अणु
	हाल 0:
		वापस "Reserved";
	हाल 1:
		वापस "Analog VGA";
	हाल 2:
		वापस "LVDS";
	हाल 3:
		वापस "Reserved";
	हाल 4:
		वापस "HDMI/DVI_B";
	हाल 5:
		वापस "HDMI/DVI_C";
	हाल 6:
		वापस "HDMI/DVI_D";
	हाल 7:
		वापस "DisplayPort_A";
	हाल 8:
		वापस "DisplayPort_B";
	हाल 9:
		वापस "DisplayPort_C";
	हाल 0xa:
		वापस "DisplayPort_D";
	हाल 0xb:
	हाल 0xc:
	हाल 0xd:
		वापस "Reserved";
	हाल 0xe:
		वापस "WiDi";
	शेष:
		वापस "bad type";
	पूर्ण
पूर्ण

अटल अक्षर *पूर्णांकel_dsm_mux_type(u8 type)
अणु
	चयन (type) अणु
	हाल 0:
		वापस "unknown";
	हाल 1:
		वापस "No MUX, iGPU only";
	हाल 2:
		वापस "No MUX, dGPU only";
	हाल 3:
		वापस "MUXed between iGPU and dGPU";
	शेष:
		वापस "bad type";
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsm_platक्रमm_mux_info(acpi_handle dhandle)
अणु
	पूर्णांक i;
	जोड़ acpi_object *pkg, *connector_count;

	pkg = acpi_evaluate_dsm_typed(dhandle, &पूर्णांकel_dsm_guid,
			INTEL_DSM_REVISION_ID, INTEL_DSM_FN_PLATFORM_MUX_INFO,
			शून्य, ACPI_TYPE_PACKAGE);
	अगर (!pkg) अणु
		DRM_DEBUG_DRIVER("failed to evaluate _DSM\n");
		वापस;
	पूर्ण

	अगर (!pkg->package.count) अणु
		DRM_DEBUG_DRIVER("no connection in _DSM\n");
		वापस;
	पूर्ण

	connector_count = &pkg->package.elements[0];
	DRM_DEBUG_DRIVER("MUX info connectors: %lld\n",
		  (अचिन्हित दीर्घ दीर्घ)connector_count->पूर्णांकeger.value);
	क्रम (i = 1; i < pkg->package.count; i++) अणु
		जोड़ acpi_object *obj = &pkg->package.elements[i];
		जोड़ acpi_object *connector_id;
		जोड़ acpi_object *info;

		अगर (obj->type != ACPI_TYPE_PACKAGE || obj->package.count < 2) अणु
			DRM_DEBUG_DRIVER("Invalid object for MUX #%d\n", i);
			जारी;
		पूर्ण

		connector_id = &obj->package.elements[0];
		info = &obj->package.elements[1];
		अगर (info->type != ACPI_TYPE_BUFFER || info->buffer.length < 4) अणु
			DRM_DEBUG_DRIVER("Invalid info for MUX obj #%d\n", i);
			जारी;
		पूर्ण

		DRM_DEBUG_DRIVER("Connector id: 0x%016llx\n",
			  (अचिन्हित दीर्घ दीर्घ)connector_id->पूर्णांकeger.value);
		DRM_DEBUG_DRIVER("  port id: %s\n",
		       पूर्णांकel_dsm_port_name(info->buffer.poपूर्णांकer[0]));
		DRM_DEBUG_DRIVER("  display mux info: %s\n",
		       पूर्णांकel_dsm_mux_type(info->buffer.poपूर्णांकer[1]));
		DRM_DEBUG_DRIVER("  aux/dc mux info: %s\n",
		       पूर्णांकel_dsm_mux_type(info->buffer.poपूर्णांकer[2]));
		DRM_DEBUG_DRIVER("  hpd mux info: %s\n",
		       पूर्णांकel_dsm_mux_type(info->buffer.poपूर्णांकer[3]));
	पूर्ण

	ACPI_FREE(pkg);
पूर्ण

अटल acpi_handle पूर्णांकel_dsm_pci_probe(काष्ठा pci_dev *pdev)
अणु
	acpi_handle dhandle;

	dhandle = ACPI_HANDLE(&pdev->dev);
	अगर (!dhandle)
		वापस शून्य;

	अगर (!acpi_check_dsm(dhandle, &पूर्णांकel_dsm_guid, INTEL_DSM_REVISION_ID,
			    1 << INTEL_DSM_FN_PLATFORM_MUX_INFO)) अणु
		DRM_DEBUG_KMS("no _DSM method for intel device\n");
		वापस शून्य;
	पूर्ण

	पूर्णांकel_dsm_platक्रमm_mux_info(dhandle);

	वापस dhandle;
पूर्ण

अटल bool पूर्णांकel_dsm_detect(व्योम)
अणु
	acpi_handle dhandle = शून्य;
	अक्षर acpi_method_name[255] = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणुमाप(acpi_method_name), acpi_method_nameपूर्ण;
	काष्ठा pci_dev *pdev = शून्य;
	पूर्णांक vga_count = 0;

	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != शून्य) अणु
		vga_count++;
		dhandle = पूर्णांकel_dsm_pci_probe(pdev) ?: dhandle;
	पूर्ण

	अगर (vga_count == 2 && dhandle) अणु
		acpi_get_name(dhandle, ACPI_FULL_PATHNAME, &buffer);
		DRM_DEBUG_DRIVER("vga_switcheroo: detected DSM switching method %s handle\n",
				 acpi_method_name);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम पूर्णांकel_रेजिस्टर_dsm_handler(व्योम)
अणु
	अगर (!पूर्णांकel_dsm_detect())
		वापस;
पूर्ण

व्योम पूर्णांकel_unरेजिस्टर_dsm_handler(व्योम)
अणु
पूर्ण

/*
 * ACPI Specअगरication, Revision 5.0, Appendix B.3.2 _DOD (Enumerate All Devices
 * Attached to the Display Adapter).
 */
#घोषणा ACPI_DISPLAY_INDEX_SHIFT		0
#घोषणा ACPI_DISPLAY_INDEX_MASK			(0xf << 0)
#घोषणा ACPI_DISPLAY_PORT_ATTACHMENT_SHIFT	4
#घोषणा ACPI_DISPLAY_PORT_ATTACHMENT_MASK	(0xf << 4)
#घोषणा ACPI_DISPLAY_TYPE_SHIFT			8
#घोषणा ACPI_DISPLAY_TYPE_MASK			(0xf << 8)
#घोषणा ACPI_DISPLAY_TYPE_OTHER			(0 << 8)
#घोषणा ACPI_DISPLAY_TYPE_VGA			(1 << 8)
#घोषणा ACPI_DISPLAY_TYPE_TV			(2 << 8)
#घोषणा ACPI_DISPLAY_TYPE_EXTERNAL_DIGITAL	(3 << 8)
#घोषणा ACPI_DISPLAY_TYPE_INTERNAL_DIGITAL	(4 << 8)
#घोषणा ACPI_VENDOR_SPECIFIC_SHIFT		12
#घोषणा ACPI_VENDOR_SPECIFIC_MASK		(0xf << 12)
#घोषणा ACPI_BIOS_CAN_DETECT			(1 << 16)
#घोषणा ACPI_DEPENDS_ON_VGA			(1 << 17)
#घोषणा ACPI_PIPE_ID_SHIFT			18
#घोषणा ACPI_PIPE_ID_MASK			(7 << 18)
#घोषणा ACPI_DEVICE_ID_SCHEME			(1ULL << 31)

अटल u32 acpi_display_type(काष्ठा पूर्णांकel_connector *connector)
अणु
	u32 display_type;

	चयन (connector->base.connector_type) अणु
	हाल DRM_MODE_CONNECTOR_VGA:
	हाल DRM_MODE_CONNECTOR_DVIA:
		display_type = ACPI_DISPLAY_TYPE_VGA;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_Composite:
	हाल DRM_MODE_CONNECTOR_SVIDEO:
	हाल DRM_MODE_CONNECTOR_Component:
	हाल DRM_MODE_CONNECTOR_9PinDIN:
	हाल DRM_MODE_CONNECTOR_TV:
		display_type = ACPI_DISPLAY_TYPE_TV;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_DisplayPort:
	हाल DRM_MODE_CONNECTOR_HDMIA:
	हाल DRM_MODE_CONNECTOR_HDMIB:
		display_type = ACPI_DISPLAY_TYPE_EXTERNAL_DIGITAL;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_LVDS:
	हाल DRM_MODE_CONNECTOR_eDP:
	हाल DRM_MODE_CONNECTOR_DSI:
		display_type = ACPI_DISPLAY_TYPE_INTERNAL_DIGITAL;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_Unknown:
	हाल DRM_MODE_CONNECTOR_VIRTUAL:
		display_type = ACPI_DISPLAY_TYPE_OTHER;
		अवरोध;
	शेष:
		MISSING_CASE(connector->base.connector_type);
		display_type = ACPI_DISPLAY_TYPE_OTHER;
		अवरोध;
	पूर्ण

	वापस display_type;
पूर्ण

व्योम पूर्णांकel_acpi_device_id_update(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *drm_dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	u8 display_index[16] = अणुपूर्ण;

	/* Populate the ACPI IDs क्रम all connectors क्रम a given drm_device */
	drm_connector_list_iter_begin(drm_dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		u32 device_id, type;

		device_id = acpi_display_type(connector);

		/* Use display type specअगरic display index. */
		type = (device_id & ACPI_DISPLAY_TYPE_MASK)
			>> ACPI_DISPLAY_TYPE_SHIFT;
		device_id |= display_index[type]++ << ACPI_DISPLAY_INDEX_SHIFT;

		connector->acpi_device_id = device_id;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
पूर्ण
