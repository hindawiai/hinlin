<शैली गुरु>
/*
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Rafaध Miधecki <zajec5@gmail.com>
 *          Alex Deucher <alexdeucher@gmail.com>
 */

#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/pci.h>
#समावेश <linux/घातer_supply.h>

#समावेश <drm/drm_vblank.h>

#समावेश "atom.h"
#समावेश "avivod.h"
#समावेश "r600_dpm.h"
#समावेश "radeon.h"
#समावेश "radeon_pm.h"

#घोषणा RADEON_IDLE_LOOP_MS 100
#घोषणा RADEON_RECLOCK_DELAY_MS 200
#घोषणा RADEON_WAIT_VBLANK_TIMEOUT 200

अटल स्थिर अक्षर *radeon_pm_state_type_name[5] = अणु
	"",
	"Powersave",
	"Battery",
	"Balanced",
	"Performance",
पूर्ण;

अटल व्योम radeon_dynpm_idle_work_handler(काष्ठा work_काष्ठा *work);
अटल व्योम radeon_debugfs_pm_init(काष्ठा radeon_device *rdev);
अटल bool radeon_pm_in_vbl(काष्ठा radeon_device *rdev);
अटल bool radeon_pm_debug_check_in_vbl(काष्ठा radeon_device *rdev, bool finish);
अटल व्योम radeon_pm_update_profile(काष्ठा radeon_device *rdev);
अटल व्योम radeon_pm_set_घड़ीs(काष्ठा radeon_device *rdev);

पूर्णांक radeon_pm_get_type_index(काष्ठा radeon_device *rdev,
			     क्रमागत radeon_pm_state_type ps_type,
			     पूर्णांक instance)
अणु
	पूर्णांक i;
	पूर्णांक found_instance = -1;

	क्रम (i = 0; i < rdev->pm.num_घातer_states; i++) अणु
		अगर (rdev->pm.घातer_state[i].type == ps_type) अणु
			found_instance++;
			अगर (found_instance == instance)
				वापस i;
		पूर्ण
	पूर्ण
	/* वापस शेष अगर no match */
	वापस rdev->pm.शेष_घातer_state_index;
पूर्ण

व्योम radeon_pm_acpi_event_handler(काष्ठा radeon_device *rdev)
अणु
	अगर ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) अणु
		mutex_lock(&rdev->pm.mutex);
		अगर (घातer_supply_is_प्रणाली_supplied() > 0)
			rdev->pm.dpm.ac_घातer = true;
		अन्यथा
			rdev->pm.dpm.ac_घातer = false;
		अगर (rdev->family == CHIP_ARUBA) अणु
			अगर (rdev->asic->dpm.enable_bapm)
				radeon_dpm_enable_bapm(rdev, rdev->pm.dpm.ac_घातer);
		पूर्ण
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण अन्यथा अगर (rdev->pm.pm_method == PM_METHOD_PROखाता) अणु
		अगर (rdev->pm.profile == PM_PROखाता_AUTO) अणु
			mutex_lock(&rdev->pm.mutex);
			radeon_pm_update_profile(rdev);
			radeon_pm_set_घड़ीs(rdev);
			mutex_unlock(&rdev->pm.mutex);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम radeon_pm_update_profile(काष्ठा radeon_device *rdev)
अणु
	चयन (rdev->pm.profile) अणु
	हाल PM_PROखाता_DEFAULT:
		rdev->pm.profile_index = PM_PROखाता_DEFAULT_IDX;
		अवरोध;
	हाल PM_PROखाता_AUTO:
		अगर (घातer_supply_is_प्रणाली_supplied() > 0) अणु
			अगर (rdev->pm.active_crtc_count > 1)
				rdev->pm.profile_index = PM_PROखाता_HIGH_MH_IDX;
			अन्यथा
				rdev->pm.profile_index = PM_PROखाता_HIGH_SH_IDX;
		पूर्ण अन्यथा अणु
			अगर (rdev->pm.active_crtc_count > 1)
				rdev->pm.profile_index = PM_PROखाता_MID_MH_IDX;
			अन्यथा
				rdev->pm.profile_index = PM_PROखाता_MID_SH_IDX;
		पूर्ण
		अवरोध;
	हाल PM_PROखाता_LOW:
		अगर (rdev->pm.active_crtc_count > 1)
			rdev->pm.profile_index = PM_PROखाता_LOW_MH_IDX;
		अन्यथा
			rdev->pm.profile_index = PM_PROखाता_LOW_SH_IDX;
		अवरोध;
	हाल PM_PROखाता_MID:
		अगर (rdev->pm.active_crtc_count > 1)
			rdev->pm.profile_index = PM_PROखाता_MID_MH_IDX;
		अन्यथा
			rdev->pm.profile_index = PM_PROखाता_MID_SH_IDX;
		अवरोध;
	हाल PM_PROखाता_HIGH:
		अगर (rdev->pm.active_crtc_count > 1)
			rdev->pm.profile_index = PM_PROखाता_HIGH_MH_IDX;
		अन्यथा
			rdev->pm.profile_index = PM_PROखाता_HIGH_SH_IDX;
		अवरोध;
	पूर्ण

	अगर (rdev->pm.active_crtc_count == 0) अणु
		rdev->pm.requested_घातer_state_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_off_ps_idx;
		rdev->pm.requested_घड़ी_mode_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_off_cm_idx;
	पूर्ण अन्यथा अणु
		rdev->pm.requested_घातer_state_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_on_ps_idx;
		rdev->pm.requested_घड़ी_mode_index =
			rdev->pm.profiles[rdev->pm.profile_index].dpms_on_cm_idx;
	पूर्ण
पूर्ण

अटल व्योम radeon_unmap_vram_bos(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_bo *bo, *n;

	अगर (list_empty(&rdev->gem.objects))
		वापस;

	list_क्रम_each_entry_safe(bo, n, &rdev->gem.objects, list) अणु
		अगर (bo->tbo.mem.mem_type == TTM_PL_VRAM)
			tपंचांग_bo_unmap_भव(&bo->tbo);
	पूर्ण
पूर्ण

अटल व्योम radeon_sync_with_vblank(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.active_crtcs) अणु
		rdev->pm.vblank_sync = false;
		रुको_event_समयout(
			rdev->irq.vblank_queue, rdev->pm.vblank_sync,
			msecs_to_jअगरfies(RADEON_WAIT_VBLANK_TIMEOUT));
	पूर्ण
पूर्ण

अटल व्योम radeon_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	u32 sclk, mclk;
	bool misc_after = false;

	अगर ((rdev->pm.requested_घड़ी_mode_index == rdev->pm.current_घड़ी_mode_index) &&
	    (rdev->pm.requested_घातer_state_index == rdev->pm.current_घातer_state_index))
		वापस;

	अगर (radeon_gui_idle(rdev)) अणु
		sclk = rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
			घड़ी_info[rdev->pm.requested_घड़ी_mode_index].sclk;
		अगर (sclk > rdev->pm.शेष_sclk)
			sclk = rdev->pm.शेष_sclk;

		/* starting with BTC, there is one state that is used क्रम both
		 * MH and SH.  Dअगरference is that we always use the high घड़ी index क्रम
		 * mclk and vddci.
		 */
		अगर ((rdev->pm.pm_method == PM_METHOD_PROखाता) &&
		    (rdev->family >= CHIP_BARTS) &&
		    rdev->pm.active_crtc_count &&
		    ((rdev->pm.profile_index == PM_PROखाता_MID_MH_IDX) ||
		     (rdev->pm.profile_index == PM_PROखाता_LOW_MH_IDX)))
			mclk = rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
				घड़ी_info[rdev->pm.profiles[PM_PROखाता_HIGH_MH_IDX].dpms_on_cm_idx].mclk;
		अन्यथा
			mclk = rdev->pm.घातer_state[rdev->pm.requested_घातer_state_index].
				घड़ी_info[rdev->pm.requested_घड़ी_mode_index].mclk;

		अगर (mclk > rdev->pm.शेष_mclk)
			mclk = rdev->pm.शेष_mclk;

		/* upvolt beक्रमe raising घड़ीs, करोwnvolt after lowering घड़ीs */
		अगर (sclk < rdev->pm.current_sclk)
			misc_after = true;

		radeon_sync_with_vblank(rdev);

		अगर (rdev->pm.pm_method == PM_METHOD_DYNPM) अणु
			अगर (!radeon_pm_in_vbl(rdev))
				वापस;
		पूर्ण

		radeon_pm_prepare(rdev);

		अगर (!misc_after)
			/* voltage, pcie lanes, etc.*/
			radeon_pm_misc(rdev);

		/* set engine घड़ी */
		अगर (sclk != rdev->pm.current_sclk) अणु
			radeon_pm_debug_check_in_vbl(rdev, false);
			radeon_set_engine_घड़ी(rdev, sclk);
			radeon_pm_debug_check_in_vbl(rdev, true);
			rdev->pm.current_sclk = sclk;
			DRM_DEBUG_DRIVER("Setting: e: %d\n", sclk);
		पूर्ण

		/* set memory घड़ी */
		अगर (rdev->asic->pm.set_memory_घड़ी && (mclk != rdev->pm.current_mclk)) अणु
			radeon_pm_debug_check_in_vbl(rdev, false);
			radeon_set_memory_घड़ी(rdev, mclk);
			radeon_pm_debug_check_in_vbl(rdev, true);
			rdev->pm.current_mclk = mclk;
			DRM_DEBUG_DRIVER("Setting: m: %d\n", mclk);
		पूर्ण

		अगर (misc_after)
			/* voltage, pcie lanes, etc.*/
			radeon_pm_misc(rdev);

		radeon_pm_finish(rdev);

		rdev->pm.current_घातer_state_index = rdev->pm.requested_घातer_state_index;
		rdev->pm.current_घड़ी_mode_index = rdev->pm.requested_घड़ी_mode_index;
	पूर्ण अन्यथा
		DRM_DEBUG_DRIVER("pm: GUI not idle!!!\n");
पूर्ण

अटल व्योम radeon_pm_set_घड़ीs(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_crtc *crtc;
	पूर्णांक i, r;

	/* no need to take locks, etc. अगर nothing's going to change */
	अगर ((rdev->pm.requested_घड़ी_mode_index == rdev->pm.current_घड़ी_mode_index) &&
	    (rdev->pm.requested_घातer_state_index == rdev->pm.current_घातer_state_index))
		वापस;

	करोwn_ग_लिखो(&rdev->pm.mclk_lock);
	mutex_lock(&rdev->ring_lock);

	/* रुको क्रम the rings to drain */
	क्रम (i = 0; i < RADEON_NUM_RINGS; i++) अणु
		काष्ठा radeon_ring *ring = &rdev->ring[i];
		अगर (!ring->पढ़ोy) अणु
			जारी;
		पूर्ण
		r = radeon_fence_रुको_empty(rdev, i);
		अगर (r) अणु
			/* needs a GPU reset करोnt reset here */
			mutex_unlock(&rdev->ring_lock);
			up_ग_लिखो(&rdev->pm.mclk_lock);
			वापस;
		पूर्ण
	पूर्ण

	radeon_unmap_vram_bos(rdev);

	अगर (rdev->irq.installed) अणु
		i = 0;
		drm_क्रम_each_crtc(crtc, rdev->ddev) अणु
			अगर (rdev->pm.active_crtcs & (1 << i)) अणु
				/* This can fail अगर a modeset is in progress */
				अगर (drm_crtc_vblank_get(crtc) == 0)
					rdev->pm.req_vblank |= (1 << i);
				अन्यथा
					DRM_DEBUG_DRIVER("crtc %d no vblank, can glitch\n",
							 i);
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	radeon_set_घातer_state(rdev);

	अगर (rdev->irq.installed) अणु
		i = 0;
		drm_क्रम_each_crtc(crtc, rdev->ddev) अणु
			अगर (rdev->pm.req_vblank & (1 << i)) अणु
				rdev->pm.req_vblank &= ~(1 << i);
				drm_crtc_vblank_put(crtc);
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	/* update display watermarks based on new घातer state */
	radeon_update_bandwidth_info(rdev);
	अगर (rdev->pm.active_crtc_count)
		radeon_bandwidth_update(rdev);

	rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;

	mutex_unlock(&rdev->ring_lock);
	up_ग_लिखो(&rdev->pm.mclk_lock);
पूर्ण

अटल व्योम radeon_pm_prपूर्णांक_states(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, j;
	काष्ठा radeon_घातer_state *घातer_state;
	काष्ठा radeon_pm_घड़ी_info *घड़ी_info;

	DRM_DEBUG_DRIVER("%d Power State(s)\n", rdev->pm.num_घातer_states);
	क्रम (i = 0; i < rdev->pm.num_घातer_states; i++) अणु
		घातer_state = &rdev->pm.घातer_state[i];
		DRM_DEBUG_DRIVER("State %d: %s\n", i,
			radeon_pm_state_type_name[घातer_state->type]);
		अगर (i == rdev->pm.शेष_घातer_state_index)
			DRM_DEBUG_DRIVER("\tDefault");
		अगर ((rdev->flags & RADEON_IS_PCIE) && !(rdev->flags & RADEON_IS_IGP))
			DRM_DEBUG_DRIVER("\t%d PCIE Lanes\n", घातer_state->pcie_lanes);
		अगर (घातer_state->flags & RADEON_PM_STATE_SINGLE_DISPLAY_ONLY)
			DRM_DEBUG_DRIVER("\tSingle display only\n");
		DRM_DEBUG_DRIVER("\t%d Clock Mode(s)\n", घातer_state->num_घड़ी_modes);
		क्रम (j = 0; j < घातer_state->num_घड़ी_modes; j++) अणु
			घड़ी_info = &(घातer_state->घड़ी_info[j]);
			अगर (rdev->flags & RADEON_IS_IGP)
				DRM_DEBUG_DRIVER("\t\t%d e: %d\n",
						 j,
						 घड़ी_info->sclk * 10);
			अन्यथा
				DRM_DEBUG_DRIVER("\t\t%d e: %d\tm: %d\tv: %d\n",
						 j,
						 घड़ी_info->sclk * 10,
						 घड़ी_info->mclk * 10,
						 घड़ी_info->voltage.voltage);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार radeon_get_pm_profile(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;
	पूर्णांक cp = rdev->pm.profile;

	वापस sysfs_emit(buf, "%s\n", (cp == PM_PROखाता_AUTO) ? "auto" :
			  (cp == PM_PROखाता_LOW) ? "low" :
			  (cp == PM_PROखाता_MID) ? "mid" :
			  (cp == PM_PROखाता_HIGH) ? "high" : "default");
पूर्ण

अटल sमाप_प्रकार radeon_set_pm_profile(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;

	/* Can't set profile when the card is off */
	अगर  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON))
		वापस -EINVAL;

	mutex_lock(&rdev->pm.mutex);
	अगर (rdev->pm.pm_method == PM_METHOD_PROखाता) अणु
		अगर (म_भेदन("default", buf, म_माप("default")) == 0)
			rdev->pm.profile = PM_PROखाता_DEFAULT;
		अन्यथा अगर (म_भेदन("auto", buf, म_माप("auto")) == 0)
			rdev->pm.profile = PM_PROखाता_AUTO;
		अन्यथा अगर (म_भेदन("low", buf, म_माप("low")) == 0)
			rdev->pm.profile = PM_PROखाता_LOW;
		अन्यथा अगर (म_भेदन("mid", buf, म_माप("mid")) == 0)
			rdev->pm.profile = PM_PROखाता_MID;
		अन्यथा अगर (म_भेदन("high", buf, म_माप("high")) == 0)
			rdev->pm.profile = PM_PROखाता_HIGH;
		अन्यथा अणु
			count = -EINVAL;
			जाओ fail;
		पूर्ण
		radeon_pm_update_profile(rdev);
		radeon_pm_set_घड़ीs(rdev);
	पूर्ण अन्यथा
		count = -EINVAL;

fail:
	mutex_unlock(&rdev->pm.mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार radeon_get_pm_method(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;
	पूर्णांक pm = rdev->pm.pm_method;

	वापस sysfs_emit(buf, "%s\n", (pm == PM_METHOD_DYNPM) ? "dynpm" :
			  (pm == PM_METHOD_PROखाता) ? "profile" : "dpm");
पूर्ण

अटल sमाप_प्रकार radeon_set_pm_method(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;

	/* Can't set method when the card is off */
	अगर  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON)) अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण

	/* we करोn't support the legacy modes with dpm */
	अगर (rdev->pm.pm_method == PM_METHOD_DPM) अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (म_भेदन("dynpm", buf, म_माप("dynpm")) == 0) अणु
		mutex_lock(&rdev->pm.mutex);
		rdev->pm.pm_method = PM_METHOD_DYNPM;
		rdev->pm.dynpm_state = DYNPM_STATE_PAUSED;
		rdev->pm.dynpm_planned_action = DYNPM_ACTION_DEFAULT;
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण अन्यथा अगर (म_भेदन("profile", buf, म_माप("profile")) == 0) अणु
		mutex_lock(&rdev->pm.mutex);
		/* disable dynpm */
		rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
		rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
		rdev->pm.pm_method = PM_METHOD_PROखाता;
		mutex_unlock(&rdev->pm.mutex);
		cancel_delayed_work_sync(&rdev->pm.dynpm_idle_work);
	पूर्ण अन्यथा अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण
	radeon_pm_compute_घड़ीs(rdev);
fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार radeon_get_dpm_state(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;
	क्रमागत radeon_pm_state_type pm = rdev->pm.dpm.user_state;

	वापस sysfs_emit(buf, "%s\n",
			  (pm == POWER_STATE_TYPE_BATTERY) ? "battery" :
			  (pm == POWER_STATE_TYPE_BALANCED) ? "balanced" : "performance");
पूर्ण

अटल sमाप_प्रकार radeon_set_dpm_state(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;

	mutex_lock(&rdev->pm.mutex);
	अगर (म_भेदन("battery", buf, म_माप("battery")) == 0)
		rdev->pm.dpm.user_state = POWER_STATE_TYPE_BATTERY;
	अन्यथा अगर (म_भेदन("balanced", buf, म_माप("balanced")) == 0)
		rdev->pm.dpm.user_state = POWER_STATE_TYPE_BALANCED;
	अन्यथा अगर (म_भेदन("performance", buf, म_माप("performance")) == 0)
		rdev->pm.dpm.user_state = POWER_STATE_TYPE_PERFORMANCE;
	अन्यथा अणु
		mutex_unlock(&rdev->pm.mutex);
		count = -EINVAL;
		जाओ fail;
	पूर्ण
	mutex_unlock(&rdev->pm.mutex);

	/* Can't set dpm state when the card is off */
	अगर (!(rdev->flags & RADEON_IS_PX) ||
	    (ddev->चयन_घातer_state == DRM_SWITCH_POWER_ON))
		radeon_pm_compute_घड़ीs(rdev);

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार radeon_get_dpm_क्रमced_perक्रमmance_level(काष्ठा device *dev,
						       काष्ठा device_attribute *attr,
						       अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;
	क्रमागत radeon_dpm_क्रमced_level level = rdev->pm.dpm.क्रमced_level;

	अगर  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON))
		वापस sysfs_emit(buf, "off\n");

	वापस sysfs_emit(buf, "%s\n",
			  (level == RADEON_DPM_FORCED_LEVEL_AUTO) ? "auto" :
			  (level == RADEON_DPM_FORCED_LEVEL_LOW) ? "low" : "high");
पूर्ण

अटल sमाप_प्रकार radeon_set_dpm_क्रमced_perक्रमmance_level(काष्ठा device *dev,
						       काष्ठा device_attribute *attr,
						       स्थिर अक्षर *buf,
						       माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा radeon_device *rdev = ddev->dev_निजी;
	क्रमागत radeon_dpm_क्रमced_level level;
	पूर्णांक ret = 0;

	/* Can't क्रमce perक्रमmance level when the card is off */
	अगर  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON))
		वापस -EINVAL;

	mutex_lock(&rdev->pm.mutex);
	अगर (म_भेदन("low", buf, म_माप("low")) == 0) अणु
		level = RADEON_DPM_FORCED_LEVEL_LOW;
	पूर्ण अन्यथा अगर (म_भेदन("high", buf, म_माप("high")) == 0) अणु
		level = RADEON_DPM_FORCED_LEVEL_HIGH;
	पूर्ण अन्यथा अगर (म_भेदन("auto", buf, म_माप("auto")) == 0) अणु
		level = RADEON_DPM_FORCED_LEVEL_AUTO;
	पूर्ण अन्यथा अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण
	अगर (rdev->asic->dpm.क्रमce_perक्रमmance_level) अणु
		अगर (rdev->pm.dpm.thermal_active) अणु
			count = -EINVAL;
			जाओ fail;
		पूर्ण
		ret = radeon_dpm_क्रमce_perक्रमmance_level(rdev, level);
		अगर (ret)
			count = -EINVAL;
	पूर्ण
fail:
	mutex_unlock(&rdev->pm.mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_get_pwm1_enable(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	u32 pwm_mode = 0;

	अगर (rdev->asic->dpm.fan_ctrl_get_mode)
		pwm_mode = rdev->asic->dpm.fan_ctrl_get_mode(rdev);

	/* never 0 (full-speed), fuse or smc-controlled always */
	वापस प्र_लिखो(buf, "%i\n", pwm_mode == FDO_PWM_MODE_STATIC ? 1 : 2);
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_set_pwm1_enable(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार count)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	पूर्णांक err;
	पूर्णांक value;

	अगर(!rdev->asic->dpm.fan_ctrl_set_mode)
		वापस -EINVAL;

	err = kstrtoपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	चयन (value) अणु
	हाल 1: /* manual, percent-based */
		rdev->asic->dpm.fan_ctrl_set_mode(rdev, FDO_PWM_MODE_STATIC);
		अवरोध;
	शेष: /* disable */
		rdev->asic->dpm.fan_ctrl_set_mode(rdev, 0);
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_get_pwm1_min(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", 0);
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_get_pwm1_max(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", 255);
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_set_pwm1(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 value;

	err = kstrtou32(buf, 10, &value);
	अगर (err)
		वापस err;

	value = (value * 100) / 255;

	err = rdev->asic->dpm.set_fan_speed_percent(rdev, value);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_get_pwm1(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 speed;

	err = rdev->asic->dpm.get_fan_speed_percent(rdev, &speed);
	अगर (err)
		वापस err;

	speed = (speed * 255) / 100;

	वापस प्र_लिखो(buf, "%i\n", speed);
पूर्ण

अटल DEVICE_ATTR(घातer_profile, S_IRUGO | S_IWUSR, radeon_get_pm_profile, radeon_set_pm_profile);
अटल DEVICE_ATTR(घातer_method, S_IRUGO | S_IWUSR, radeon_get_pm_method, radeon_set_pm_method);
अटल DEVICE_ATTR(घातer_dpm_state, S_IRUGO | S_IWUSR, radeon_get_dpm_state, radeon_set_dpm_state);
अटल DEVICE_ATTR(घातer_dpm_क्रमce_perक्रमmance_level, S_IRUGO | S_IWUSR,
		   radeon_get_dpm_क्रमced_perक्रमmance_level,
		   radeon_set_dpm_क्रमced_perक्रमmance_level);

अटल sमाप_प्रकार radeon_hwmon_show_temp(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	काष्ठा drm_device *ddev = rdev->ddev;
	पूर्णांक temp;

	/* Can't get temperature when the card is off */
	अगर  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON))
		वापस -EINVAL;

	अगर (rdev->asic->pm.get_temperature)
		temp = radeon_get_temperature(rdev);
	अन्यथा
		temp = 0;

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार radeon_hwmon_show_temp_thresh(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	पूर्णांक hyst = to_sensor_dev_attr(attr)->index;
	पूर्णांक temp;

	अगर (hyst)
		temp = rdev->pm.dpm.thermal.min_temp;
	अन्यथा
		temp = rdev->pm.dpm.thermal.max_temp;

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, radeon_hwmon_show_temp, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_crit, S_IRUGO, radeon_hwmon_show_temp_thresh, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_crit_hyst, S_IRUGO, radeon_hwmon_show_temp_thresh, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(pwm1, S_IRUGO | S_IWUSR, radeon_hwmon_get_pwm1, radeon_hwmon_set_pwm1, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_enable, S_IRUGO | S_IWUSR, radeon_hwmon_get_pwm1_enable, radeon_hwmon_set_pwm1_enable, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_min, S_IRUGO, radeon_hwmon_get_pwm1_min, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_max, S_IRUGO, radeon_hwmon_get_pwm1_max, शून्य, 0);

अटल sमाप_प्रकार radeon_hwmon_show_sclk(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	काष्ठा drm_device *ddev = rdev->ddev;
	u32 sclk = 0;

	/* Can't get घड़ी frequency when the card is off */
	अगर ((rdev->flags & RADEON_IS_PX) &&
	    (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON))
		वापस -EINVAL;

	अगर (rdev->asic->dpm.get_current_sclk)
		sclk = radeon_dpm_get_current_sclk(rdev);

	/* Value वापसed by dpm is in 10 KHz units, need to convert it पूर्णांकo Hz 
	   क्रम hwmon */
	sclk *= 10000;

	वापस sysfs_emit(buf, "%u\n", sclk);
पूर्ण

अटल SENSOR_DEVICE_ATTR(freq1_input, S_IRUGO, radeon_hwmon_show_sclk, शून्य,
			  0);

अटल sमाप_प्रकार radeon_hwmon_show_vddc(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	काष्ठा drm_device *ddev = rdev->ddev;
	u16 vddc = 0;

	/* Can't get vddc when the card is off */
	अगर ((rdev->flags & RADEON_IS_PX) &&
		(ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON))
		वापस -EINVAL;

	अगर (rdev->asic->dpm.get_current_vddc)
		vddc = rdev->asic->dpm.get_current_vddc(rdev);

	वापस sysfs_emit(buf, "%u\n", vddc);
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_input, S_IRUGO, radeon_hwmon_show_vddc, शून्य,
			  0);

अटल काष्ठा attribute *hwmon_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_min.dev_attr.attr,
	&sensor_dev_attr_pwm1_max.dev_attr.attr,
	&sensor_dev_attr_freq1_input.dev_attr.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल umode_t hwmon_attributes_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा radeon_device *rdev = dev_get_drvdata(dev);
	umode_t effective_mode = attr->mode;

	/* Skip attributes अगर DPM is not enabled */
	अगर (rdev->pm.pm_method != PM_METHOD_DPM &&
	    (attr == &sensor_dev_attr_temp1_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_freq1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_in0_input.dev_attr.attr))
		वापस 0;

	/* Skip vddc attribute अगर get_current_vddc is not implemented */
	अगर(attr == &sensor_dev_attr_in0_input.dev_attr.attr &&
		!rdev->asic->dpm.get_current_vddc)
		वापस 0;

	/* Skip fan attributes अगर fan is not present */
	अगर (rdev->pm.no_fan &&
	    (attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr))
		वापस 0;

	/* mask fan attributes अगर we have no bindings क्रम this asic to expose */
	अगर ((!rdev->asic->dpm.get_fan_speed_percent &&
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr) || /* can't query fan */
	    (!rdev->asic->dpm.fan_ctrl_get_mode &&
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr)) /* can't query state */
		effective_mode &= ~S_IRUGO;

	अगर ((!rdev->asic->dpm.set_fan_speed_percent &&
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr) || /* can't manage fan */
	    (!rdev->asic->dpm.fan_ctrl_set_mode &&
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr)) /* can't manage state */
		effective_mode &= ~S_IWUSR;

	/* hide max/min values अगर we can't both query and manage the fan */
	अगर ((!rdev->asic->dpm.set_fan_speed_percent &&
	     !rdev->asic->dpm.get_fan_speed_percent) &&
	    (attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr))
		वापस 0;

	वापस effective_mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group hwmon_attrgroup = अणु
	.attrs = hwmon_attributes,
	.is_visible = hwmon_attributes_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hwmon_groups[] = अणु
	&hwmon_attrgroup,
	शून्य
पूर्ण;

अटल पूर्णांक radeon_hwmon_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक err = 0;

	चयन (rdev->pm.पूर्णांक_thermal_type) अणु
	हाल THERMAL_TYPE_RV6XX:
	हाल THERMAL_TYPE_RV770:
	हाल THERMAL_TYPE_EVERGREEN:
	हाल THERMAL_TYPE_NI:
	हाल THERMAL_TYPE_SUMO:
	हाल THERMAL_TYPE_SI:
	हाल THERMAL_TYPE_CI:
	हाल THERMAL_TYPE_KV:
		अगर (rdev->asic->pm.get_temperature == शून्य)
			वापस err;
		rdev->pm.पूर्णांक_hwmon_dev = hwmon_device_रेजिस्टर_with_groups(rdev->dev,
									   "radeon", rdev,
									   hwmon_groups);
		अगर (IS_ERR(rdev->pm.पूर्णांक_hwmon_dev)) अणु
			err = PTR_ERR(rdev->pm.पूर्णांक_hwmon_dev);
			dev_err(rdev->dev,
				"Unable to register hwmon device: %d\n", err);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम radeon_hwmon_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.पूर्णांक_hwmon_dev)
		hwmon_device_unरेजिस्टर(rdev->pm.पूर्णांक_hwmon_dev);
पूर्ण

अटल व्योम radeon_dpm_thermal_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev =
		container_of(work, काष्ठा radeon_device,
			     pm.dpm.thermal.work);
	/* चयन to the thermal state */
	क्रमागत radeon_pm_state_type dpm_state = POWER_STATE_TYPE_INTERNAL_THERMAL;

	अगर (!rdev->pm.dpm_enabled)
		वापस;

	अगर (rdev->asic->pm.get_temperature) अणु
		पूर्णांक temp = radeon_get_temperature(rdev);

		अगर (temp < rdev->pm.dpm.thermal.min_temp)
			/* चयन back the user state */
			dpm_state = rdev->pm.dpm.user_state;
	पूर्ण अन्यथा अणु
		अगर (rdev->pm.dpm.thermal.high_to_low)
			/* चयन back the user state */
			dpm_state = rdev->pm.dpm.user_state;
	पूर्ण
	mutex_lock(&rdev->pm.mutex);
	अगर (dpm_state == POWER_STATE_TYPE_INTERNAL_THERMAL)
		rdev->pm.dpm.thermal_active = true;
	अन्यथा
		rdev->pm.dpm.thermal_active = false;
	rdev->pm.dpm.state = dpm_state;
	mutex_unlock(&rdev->pm.mutex);

	radeon_pm_compute_घड़ीs(rdev);
पूर्ण

अटल bool radeon_dpm_single_display(काष्ठा radeon_device *rdev)
अणु
	bool single_display = (rdev->pm.dpm.new_active_crtc_count < 2) ?
		true : false;

	/* check अगर the vblank period is too लघु to adjust the mclk */
	अगर (single_display && rdev->asic->dpm.vblank_too_लघु) अणु
		अगर (radeon_dpm_vblank_too_लघु(rdev))
			single_display = false;
	पूर्ण

	/* 120hz tends to be problematic even अगर they are under the
	 * vblank limit.
	 */
	अगर (single_display && (r600_dpm_get_vrefresh(rdev) >= 120))
		single_display = false;

	वापस single_display;
पूर्ण

अटल काष्ठा radeon_ps *radeon_dpm_pick_घातer_state(काष्ठा radeon_device *rdev,
						     क्रमागत radeon_pm_state_type dpm_state)
अणु
	पूर्णांक i;
	काष्ठा radeon_ps *ps;
	u32 ui_class;
	bool single_display = radeon_dpm_single_display(rdev);

	/* certain older asics have a separare 3D perक्रमmance state,
	 * so try that first अगर the user selected perक्रमmance
	 */
	अगर (dpm_state == POWER_STATE_TYPE_PERFORMANCE)
		dpm_state = POWER_STATE_TYPE_INTERNAL_3DPERF;
	/* balanced states करोn't exist at the moment */
	अगर (dpm_state == POWER_STATE_TYPE_BALANCED)
		dpm_state = POWER_STATE_TYPE_PERFORMANCE;

restart_search:
	/* Pick the best घातer state based on current conditions */
	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		ps = &rdev->pm.dpm.ps[i];
		ui_class = ps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK;
		चयन (dpm_state) अणु
		/* user states */
		हाल POWER_STATE_TYPE_BATTERY:
			अगर (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY) अणु
				अगर (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) अणु
					अगर (single_display)
						वापस ps;
				पूर्ण अन्यथा
					वापस ps;
			पूर्ण
			अवरोध;
		हाल POWER_STATE_TYPE_BALANCED:
			अगर (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_BALANCED) अणु
				अगर (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) अणु
					अगर (single_display)
						वापस ps;
				पूर्ण अन्यथा
					वापस ps;
			पूर्ण
			अवरोध;
		हाल POWER_STATE_TYPE_PERFORMANCE:
			अगर (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) अणु
				अगर (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) अणु
					अगर (single_display)
						वापस ps;
				पूर्ण अन्यथा
					वापस ps;
			पूर्ण
			अवरोध;
		/* पूर्णांकernal states */
		हाल POWER_STATE_TYPE_INTERNAL_UVD:
			अगर (rdev->pm.dpm.uvd_ps)
				वापस rdev->pm.dpm.uvd_ps;
			अन्यथा
				अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_SD:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_HD:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_HD2:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_MVC:
			अगर (ps->class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_BOOT:
			वापस rdev->pm.dpm.boot_ps;
		हाल POWER_STATE_TYPE_INTERNAL_THERMAL:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_ACPI:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_ACPI)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_ULV:
			अगर (ps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_3DPERF:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
				वापस ps;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	/* use a fallback state अगर we didn't match */
	चयन (dpm_state) अणु
	हाल POWER_STATE_TYPE_INTERNAL_UVD_SD:
		dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
		जाओ restart_search;
	हाल POWER_STATE_TYPE_INTERNAL_UVD_HD:
	हाल POWER_STATE_TYPE_INTERNAL_UVD_HD2:
	हाल POWER_STATE_TYPE_INTERNAL_UVD_MVC:
		अगर (rdev->pm.dpm.uvd_ps) अणु
			वापस rdev->pm.dpm.uvd_ps;
		पूर्ण अन्यथा अणु
			dpm_state = POWER_STATE_TYPE_PERFORMANCE;
			जाओ restart_search;
		पूर्ण
	हाल POWER_STATE_TYPE_INTERNAL_THERMAL:
		dpm_state = POWER_STATE_TYPE_INTERNAL_ACPI;
		जाओ restart_search;
	हाल POWER_STATE_TYPE_INTERNAL_ACPI:
		dpm_state = POWER_STATE_TYPE_BATTERY;
		जाओ restart_search;
	हाल POWER_STATE_TYPE_BATTERY:
	हाल POWER_STATE_TYPE_BALANCED:
	हाल POWER_STATE_TYPE_INTERNAL_3DPERF:
		dpm_state = POWER_STATE_TYPE_PERFORMANCE;
		जाओ restart_search;
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम radeon_dpm_change_घातer_state_locked(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	काष्ठा radeon_ps *ps;
	क्रमागत radeon_pm_state_type dpm_state;
	पूर्णांक ret;
	bool single_display = radeon_dpm_single_display(rdev);

	/* अगर dpm init failed */
	अगर (!rdev->pm.dpm_enabled)
		वापस;

	अगर (rdev->pm.dpm.user_state != rdev->pm.dpm.state) अणु
		/* add other state override checks here */
		अगर ((!rdev->pm.dpm.thermal_active) &&
		    (!rdev->pm.dpm.uvd_active))
			rdev->pm.dpm.state = rdev->pm.dpm.user_state;
	पूर्ण
	dpm_state = rdev->pm.dpm.state;

	ps = radeon_dpm_pick_घातer_state(rdev, dpm_state);
	अगर (ps)
		rdev->pm.dpm.requested_ps = ps;
	अन्यथा
		वापस;

	/* no need to reprogram अगर nothing changed unless we are on BTC+ */
	अगर (rdev->pm.dpm.current_ps == rdev->pm.dpm.requested_ps) अणु
		/* vce just modअगरies an existing state so क्रमce a change */
		अगर (ps->vce_active != rdev->pm.dpm.vce_active)
			जाओ क्रमce;
		/* user has made a display change (such as timing) */
		अगर (rdev->pm.dpm.single_display != single_display)
			जाओ क्रमce;
		अगर ((rdev->family < CHIP_BARTS) || (rdev->flags & RADEON_IS_IGP)) अणु
			/* क्रम pre-BTC and APUs अगर the num crtcs changed but state is the same,
			 * all we need to करो is update the display configuration.
			 */
			अगर (rdev->pm.dpm.new_active_crtcs != rdev->pm.dpm.current_active_crtcs) अणु
				/* update display watermarks based on new घातer state */
				radeon_bandwidth_update(rdev);
				/* update displays */
				radeon_dpm_display_configuration_changed(rdev);
				rdev->pm.dpm.current_active_crtcs = rdev->pm.dpm.new_active_crtcs;
				rdev->pm.dpm.current_active_crtc_count = rdev->pm.dpm.new_active_crtc_count;
			पूर्ण
			वापस;
		पूर्ण अन्यथा अणु
			/* क्रम BTC+ अगर the num crtcs hasn't changed and state is the same,
			 * nothing to करो, अगर the num crtcs is > 1 and state is the same,
			 * update display configuration.
			 */
			अगर (rdev->pm.dpm.new_active_crtcs ==
			    rdev->pm.dpm.current_active_crtcs) अणु
				वापस;
			पूर्ण अन्यथा अणु
				अगर ((rdev->pm.dpm.current_active_crtc_count > 1) &&
				    (rdev->pm.dpm.new_active_crtc_count > 1)) अणु
					/* update display watermarks based on new घातer state */
					radeon_bandwidth_update(rdev);
					/* update displays */
					radeon_dpm_display_configuration_changed(rdev);
					rdev->pm.dpm.current_active_crtcs = rdev->pm.dpm.new_active_crtcs;
					rdev->pm.dpm.current_active_crtc_count = rdev->pm.dpm.new_active_crtc_count;
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

क्रमce:
	अगर (radeon_dpm == 1) अणु
		prपूर्णांकk("switching from power state:\n");
		radeon_dpm_prपूर्णांक_घातer_state(rdev, rdev->pm.dpm.current_ps);
		prपूर्णांकk("switching to power state:\n");
		radeon_dpm_prपूर्णांक_घातer_state(rdev, rdev->pm.dpm.requested_ps);
	पूर्ण

	करोwn_ग_लिखो(&rdev->pm.mclk_lock);
	mutex_lock(&rdev->ring_lock);

	/* update whether vce is active */
	ps->vce_active = rdev->pm.dpm.vce_active;

	ret = radeon_dpm_pre_set_घातer_state(rdev);
	अगर (ret)
		जाओ करोne;

	/* update display watermarks based on new घातer state */
	radeon_bandwidth_update(rdev);
	/* update displays */
	radeon_dpm_display_configuration_changed(rdev);

	/* रुको क्रम the rings to drain */
	क्रम (i = 0; i < RADEON_NUM_RINGS; i++) अणु
		काष्ठा radeon_ring *ring = &rdev->ring[i];
		अगर (ring->पढ़ोy)
			radeon_fence_रुको_empty(rdev, i);
	पूर्ण

	/* program the new घातer state */
	radeon_dpm_set_घातer_state(rdev);

	/* update current घातer state */
	rdev->pm.dpm.current_ps = rdev->pm.dpm.requested_ps;

	radeon_dpm_post_set_घातer_state(rdev);

	rdev->pm.dpm.current_active_crtcs = rdev->pm.dpm.new_active_crtcs;
	rdev->pm.dpm.current_active_crtc_count = rdev->pm.dpm.new_active_crtc_count;
	rdev->pm.dpm.single_display = single_display;

	अगर (rdev->asic->dpm.क्रमce_perक्रमmance_level) अणु
		अगर (rdev->pm.dpm.thermal_active) अणु
			क्रमागत radeon_dpm_क्रमced_level level = rdev->pm.dpm.क्रमced_level;
			/* क्रमce low perf level क्रम thermal */
			radeon_dpm_क्रमce_perक्रमmance_level(rdev, RADEON_DPM_FORCED_LEVEL_LOW);
			/* save the user's level */
			rdev->pm.dpm.क्रमced_level = level;
		पूर्ण अन्यथा अणु
			/* otherwise, user selected level */
			radeon_dpm_क्रमce_perक्रमmance_level(rdev, rdev->pm.dpm.क्रमced_level);
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&rdev->ring_lock);
	up_ग_लिखो(&rdev->pm.mclk_lock);
पूर्ण

व्योम radeon_dpm_enable_uvd(काष्ठा radeon_device *rdev, bool enable)
अणु
	क्रमागत radeon_pm_state_type dpm_state;

	अगर (rdev->asic->dpm.घातergate_uvd) अणु
		mutex_lock(&rdev->pm.mutex);
		/* करोn't घातergate anything अगर we
		   have active but छोड़ो streams */
		enable |= rdev->pm.dpm.sd > 0;
		enable |= rdev->pm.dpm.hd > 0;
		/* enable/disable UVD */
		radeon_dpm_घातergate_uvd(rdev, !enable);
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण अन्यथा अणु
		अगर (enable) अणु
			mutex_lock(&rdev->pm.mutex);
			rdev->pm.dpm.uvd_active = true;
			/* disable this क्रम now */
#अगर 0
			अगर ((rdev->pm.dpm.sd == 1) && (rdev->pm.dpm.hd == 0))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_SD;
			अन्यथा अगर ((rdev->pm.dpm.sd == 2) && (rdev->pm.dpm.hd == 0))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
			अन्यथा अगर ((rdev->pm.dpm.sd == 0) && (rdev->pm.dpm.hd == 1))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
			अन्यथा अगर ((rdev->pm.dpm.sd == 0) && (rdev->pm.dpm.hd == 2))
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD2;
			अन्यथा
#पूर्ण_अगर
				dpm_state = POWER_STATE_TYPE_INTERNAL_UVD;
			rdev->pm.dpm.state = dpm_state;
			mutex_unlock(&rdev->pm.mutex);
		पूर्ण अन्यथा अणु
			mutex_lock(&rdev->pm.mutex);
			rdev->pm.dpm.uvd_active = false;
			mutex_unlock(&rdev->pm.mutex);
		पूर्ण

		radeon_pm_compute_घड़ीs(rdev);
	पूर्ण
पूर्ण

व्योम radeon_dpm_enable_vce(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable) अणु
		mutex_lock(&rdev->pm.mutex);
		rdev->pm.dpm.vce_active = true;
		/* XXX select vce level based on ring/task */
		rdev->pm.dpm.vce_level = RADEON_VCE_LEVEL_AC_ALL;
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण अन्यथा अणु
		mutex_lock(&rdev->pm.mutex);
		rdev->pm.dpm.vce_active = false;
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण

	radeon_pm_compute_घड़ीs(rdev);
पूर्ण

अटल व्योम radeon_pm_suspend_old(काष्ठा radeon_device *rdev)
अणु
	mutex_lock(&rdev->pm.mutex);
	अगर (rdev->pm.pm_method == PM_METHOD_DYNPM) अणु
		अगर (rdev->pm.dynpm_state == DYNPM_STATE_ACTIVE)
			rdev->pm.dynpm_state = DYNPM_STATE_SUSPENDED;
	पूर्ण
	mutex_unlock(&rdev->pm.mutex);

	cancel_delayed_work_sync(&rdev->pm.dynpm_idle_work);
पूर्ण

अटल व्योम radeon_pm_suspend_dpm(काष्ठा radeon_device *rdev)
अणु
	mutex_lock(&rdev->pm.mutex);
	/* disable dpm */
	radeon_dpm_disable(rdev);
	/* reset the घातer state */
	rdev->pm.dpm.current_ps = rdev->pm.dpm.requested_ps = rdev->pm.dpm.boot_ps;
	rdev->pm.dpm_enabled = false;
	mutex_unlock(&rdev->pm.mutex);
पूर्ण

व्योम radeon_pm_suspend(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_suspend_dpm(rdev);
	अन्यथा
		radeon_pm_suspend_old(rdev);
पूर्ण

अटल व्योम radeon_pm_resume_old(काष्ठा radeon_device *rdev)
अणु
	/* set up the शेष घड़ीs अगर the MC ucode is loaded */
	अगर ((rdev->family >= CHIP_BARTS) &&
	    (rdev->family <= CHIP_CAYMAN) &&
	    rdev->mc_fw) अणु
		अगर (rdev->pm.शेष_vddc)
			radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddc,
						SET_VOLTAGE_TYPE_ASIC_VDDC);
		अगर (rdev->pm.शेष_vddci)
			radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddci,
						SET_VOLTAGE_TYPE_ASIC_VDDCI);
		अगर (rdev->pm.शेष_sclk)
			radeon_set_engine_घड़ी(rdev, rdev->pm.शेष_sclk);
		अगर (rdev->pm.शेष_mclk)
			radeon_set_memory_घड़ी(rdev, rdev->pm.शेष_mclk);
	पूर्ण
	/* asic init will reset the शेष घातer state */
	mutex_lock(&rdev->pm.mutex);
	rdev->pm.current_घातer_state_index = rdev->pm.शेष_घातer_state_index;
	rdev->pm.current_घड़ी_mode_index = 0;
	rdev->pm.current_sclk = rdev->pm.शेष_sclk;
	rdev->pm.current_mclk = rdev->pm.शेष_mclk;
	अगर (rdev->pm.घातer_state) अणु
		rdev->pm.current_vddc = rdev->pm.घातer_state[rdev->pm.शेष_घातer_state_index].घड़ी_info[0].voltage.voltage;
		rdev->pm.current_vddci = rdev->pm.घातer_state[rdev->pm.शेष_घातer_state_index].घड़ी_info[0].voltage.vddci;
	पूर्ण
	अगर (rdev->pm.pm_method == PM_METHOD_DYNPM
	    && rdev->pm.dynpm_state == DYNPM_STATE_SUSPENDED) अणु
		rdev->pm.dynpm_state = DYNPM_STATE_ACTIVE;
		schedule_delayed_work(&rdev->pm.dynpm_idle_work,
				      msecs_to_jअगरfies(RADEON_IDLE_LOOP_MS));
	पूर्ण
	mutex_unlock(&rdev->pm.mutex);
	radeon_pm_compute_घड़ीs(rdev);
पूर्ण

अटल व्योम radeon_pm_resume_dpm(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	/* asic init will reset to the boot state */
	mutex_lock(&rdev->pm.mutex);
	rdev->pm.dpm.current_ps = rdev->pm.dpm.requested_ps = rdev->pm.dpm.boot_ps;
	radeon_dpm_setup_asic(rdev);
	ret = radeon_dpm_enable(rdev);
	mutex_unlock(&rdev->pm.mutex);
	अगर (ret)
		जाओ dpm_resume_fail;
	rdev->pm.dpm_enabled = true;
	वापस;

dpm_resume_fail:
	DRM_ERROR("radeon: dpm resume failed\n");
	अगर ((rdev->family >= CHIP_BARTS) &&
	    (rdev->family <= CHIP_CAYMAN) &&
	    rdev->mc_fw) अणु
		अगर (rdev->pm.शेष_vddc)
			radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddc,
						SET_VOLTAGE_TYPE_ASIC_VDDC);
		अगर (rdev->pm.शेष_vddci)
			radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddci,
						SET_VOLTAGE_TYPE_ASIC_VDDCI);
		अगर (rdev->pm.शेष_sclk)
			radeon_set_engine_घड़ी(rdev, rdev->pm.शेष_sclk);
		अगर (rdev->pm.शेष_mclk)
			radeon_set_memory_घड़ी(rdev, rdev->pm.शेष_mclk);
	पूर्ण
पूर्ण

व्योम radeon_pm_resume(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_resume_dpm(rdev);
	अन्यथा
		radeon_pm_resume_old(rdev);
पूर्ण

अटल पूर्णांक radeon_pm_init_old(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	rdev->pm.profile = PM_PROखाता_DEFAULT;
	rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
	rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
	rdev->pm.dynpm_can_upघड़ी = true;
	rdev->pm.dynpm_can_करोwnघड़ी = true;
	rdev->pm.शेष_sclk = rdev->घड़ी.शेष_sclk;
	rdev->pm.शेष_mclk = rdev->घड़ी.शेष_mclk;
	rdev->pm.current_sclk = rdev->घड़ी.शेष_sclk;
	rdev->pm.current_mclk = rdev->घड़ी.शेष_mclk;
	rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_NONE;

	अगर (rdev->bios) अणु
		अगर (rdev->is_atom_bios)
			radeon_atombios_get_घातer_modes(rdev);
		अन्यथा
			radeon_combios_get_घातer_modes(rdev);
		radeon_pm_prपूर्णांक_states(rdev);
		radeon_pm_init_profile(rdev);
		/* set up the शेष घड़ीs अगर the MC ucode is loaded */
		अगर ((rdev->family >= CHIP_BARTS) &&
		    (rdev->family <= CHIP_CAYMAN) &&
		    rdev->mc_fw) अणु
			अगर (rdev->pm.शेष_vddc)
				radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddc,
							SET_VOLTAGE_TYPE_ASIC_VDDC);
			अगर (rdev->pm.शेष_vddci)
				radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddci,
							SET_VOLTAGE_TYPE_ASIC_VDDCI);
			अगर (rdev->pm.शेष_sclk)
				radeon_set_engine_घड़ी(rdev, rdev->pm.शेष_sclk);
			अगर (rdev->pm.शेष_mclk)
				radeon_set_memory_घड़ी(rdev, rdev->pm.शेष_mclk);
		पूर्ण
	पूर्ण

	/* set up the पूर्णांकernal thermal sensor अगर applicable */
	ret = radeon_hwmon_init(rdev);
	अगर (ret)
		वापस ret;

	INIT_DELAYED_WORK(&rdev->pm.dynpm_idle_work, radeon_dynpm_idle_work_handler);

	अगर (rdev->pm.num_घातer_states > 1) अणु
		radeon_debugfs_pm_init(rdev);
		DRM_INFO("radeon: power management initialized\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम radeon_dpm_prपूर्णांक_घातer_states(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		prपूर्णांकk("== power state %d ==\n", i);
		radeon_dpm_prपूर्णांक_घातer_state(rdev, &rdev->pm.dpm.ps[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_pm_init_dpm(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	/* शेष to balanced state */
	rdev->pm.dpm.state = POWER_STATE_TYPE_BALANCED;
	rdev->pm.dpm.user_state = POWER_STATE_TYPE_BALANCED;
	rdev->pm.dpm.क्रमced_level = RADEON_DPM_FORCED_LEVEL_AUTO;
	rdev->pm.शेष_sclk = rdev->घड़ी.शेष_sclk;
	rdev->pm.शेष_mclk = rdev->घड़ी.शेष_mclk;
	rdev->pm.current_sclk = rdev->घड़ी.शेष_sclk;
	rdev->pm.current_mclk = rdev->घड़ी.शेष_mclk;
	rdev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_NONE;

	अगर (rdev->bios && rdev->is_atom_bios)
		radeon_atombios_get_घातer_modes(rdev);
	अन्यथा
		वापस -EINVAL;

	/* set up the पूर्णांकernal thermal sensor अगर applicable */
	ret = radeon_hwmon_init(rdev);
	अगर (ret)
		वापस ret;

	INIT_WORK(&rdev->pm.dpm.thermal.work, radeon_dpm_thermal_work_handler);
	mutex_lock(&rdev->pm.mutex);
	radeon_dpm_init(rdev);
	rdev->pm.dpm.current_ps = rdev->pm.dpm.requested_ps = rdev->pm.dpm.boot_ps;
	अगर (radeon_dpm == 1)
		radeon_dpm_prपूर्णांक_घातer_states(rdev);
	radeon_dpm_setup_asic(rdev);
	ret = radeon_dpm_enable(rdev);
	mutex_unlock(&rdev->pm.mutex);
	अगर (ret)
		जाओ dpm_failed;
	rdev->pm.dpm_enabled = true;

	radeon_debugfs_pm_init(rdev);

	DRM_INFO("radeon: dpm initialized\n");

	वापस 0;

dpm_failed:
	rdev->pm.dpm_enabled = false;
	अगर ((rdev->family >= CHIP_BARTS) &&
	    (rdev->family <= CHIP_CAYMAN) &&
	    rdev->mc_fw) अणु
		अगर (rdev->pm.शेष_vddc)
			radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddc,
						SET_VOLTAGE_TYPE_ASIC_VDDC);
		अगर (rdev->pm.शेष_vddci)
			radeon_atom_set_voltage(rdev, rdev->pm.शेष_vddci,
						SET_VOLTAGE_TYPE_ASIC_VDDCI);
		अगर (rdev->pm.शेष_sclk)
			radeon_set_engine_घड़ी(rdev, rdev->pm.शेष_sclk);
		अगर (rdev->pm.शेष_mclk)
			radeon_set_memory_घड़ी(rdev, rdev->pm.शेष_mclk);
	पूर्ण
	DRM_ERROR("radeon: dpm initialization failed\n");
	वापस ret;
पूर्ण

काष्ठा radeon_dpm_quirk अणु
	u32 chip_venकरोr;
	u32 chip_device;
	u32 subsys_venकरोr;
	u32 subsys_device;
पूर्ण;

/* cards with dpm stability problems */
अटल काष्ठा radeon_dpm_quirk radeon_dpm_quirk_list[] = अणु
	/* TURKS - https://bugs.launchpad.net/ubuntu/+source/linux/+bug/1386534 */
	अणु PCI_VENDOR_ID_ATI, 0x6759, 0x1682, 0x3195 पूर्ण,
	/* TURKS - https://bugzilla.kernel.org/show_bug.cgi?id=83731 */
	अणु PCI_VENDOR_ID_ATI, 0x6840, 0x1179, 0xfb81 पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण,
पूर्ण;

पूर्णांक radeon_pm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_dpm_quirk *p = radeon_dpm_quirk_list;
	bool disable_dpm = false;

	/* Apply dpm quirks */
	जबतक (p && p->chip_device != 0) अणु
		अगर (rdev->pdev->venकरोr == p->chip_venकरोr &&
		    rdev->pdev->device == p->chip_device &&
		    rdev->pdev->subप्रणाली_venकरोr == p->subsys_venकरोr &&
		    rdev->pdev->subप्रणाली_device == p->subsys_device) अणु
			disable_dpm = true;
			अवरोध;
		पूर्ण
		++p;
	पूर्ण

	/* enable dpm on rv6xx+ */
	चयन (rdev->family) अणु
	हाल CHIP_RV610:
	हाल CHIP_RV630:
	हाल CHIP_RV620:
	हाल CHIP_RV635:
	हाल CHIP_RV670:
	हाल CHIP_RS780:
	हाल CHIP_RS880:
	हाल CHIP_RV770:
		/* DPM requires the RLC, RV770+ dGPU requires SMC */
		अगर (!rdev->rlc_fw)
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अन्यथा अगर ((rdev->family >= CHIP_RV770) &&
			 (!(rdev->flags & RADEON_IS_IGP)) &&
			 (!rdev->smc_fw))
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अन्यथा अगर (radeon_dpm == 1)
			rdev->pm.pm_method = PM_METHOD_DPM;
		अन्यथा
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अवरोध;
	हाल CHIP_RV730:
	हाल CHIP_RV710:
	हाल CHIP_RV740:
	हाल CHIP_CEDAR:
	हाल CHIP_REDWOOD:
	हाल CHIP_JUNIPER:
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
	हाल CHIP_PALM:
	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
	हाल CHIP_BARTS:
	हाल CHIP_TURKS:
	हाल CHIP_CAICOS:
	हाल CHIP_CAYMAN:
	हाल CHIP_ARUBA:
	हाल CHIP_TAHITI:
	हाल CHIP_PITCAIRN:
	हाल CHIP_VERDE:
	हाल CHIP_OLAND:
	हाल CHIP_HAIन_अंक:
	हाल CHIP_BONAIRE:
	हाल CHIP_KABINI:
	हाल CHIP_KAVERI:
	हाल CHIP_HAWAII:
	हाल CHIP_MULLINS:
		/* DPM requires the RLC, RV770+ dGPU requires SMC */
		अगर (!rdev->rlc_fw)
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अन्यथा अगर ((rdev->family >= CHIP_RV770) &&
			 (!(rdev->flags & RADEON_IS_IGP)) &&
			 (!rdev->smc_fw))
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अन्यथा अगर (disable_dpm && (radeon_dpm == -1))
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अन्यथा अगर (radeon_dpm == 0)
			rdev->pm.pm_method = PM_METHOD_PROखाता;
		अन्यथा
			rdev->pm.pm_method = PM_METHOD_DPM;
		अवरोध;
	शेष:
		/* शेष to profile method */
		rdev->pm.pm_method = PM_METHOD_PROखाता;
		अवरोध;
	पूर्ण

	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		वापस radeon_pm_init_dpm(rdev);
	अन्यथा
		वापस radeon_pm_init_old(rdev);
पूर्ण

पूर्णांक radeon_pm_late_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret = 0;

	अगर (rdev->pm.pm_method == PM_METHOD_DPM) अणु
		अगर (rdev->pm.dpm_enabled) अणु
			अगर (!rdev->pm.sysfs_initialized) अणु
				ret = device_create_file(rdev->dev, &dev_attr_घातer_dpm_state);
				अगर (ret)
					DRM_ERROR("failed to create device file for dpm state\n");
				ret = device_create_file(rdev->dev, &dev_attr_घातer_dpm_क्रमce_perक्रमmance_level);
				अगर (ret)
					DRM_ERROR("failed to create device file for dpm state\n");
				/* XXX: these are noops क्रम dpm but are here क्रम backwards compat */
				ret = device_create_file(rdev->dev, &dev_attr_घातer_profile);
				अगर (ret)
					DRM_ERROR("failed to create device file for power profile\n");
				ret = device_create_file(rdev->dev, &dev_attr_घातer_method);
				अगर (ret)
					DRM_ERROR("failed to create device file for power method\n");
				rdev->pm.sysfs_initialized = true;
			पूर्ण

			mutex_lock(&rdev->pm.mutex);
			ret = radeon_dpm_late_enable(rdev);
			mutex_unlock(&rdev->pm.mutex);
			अगर (ret) अणु
				rdev->pm.dpm_enabled = false;
				DRM_ERROR("radeon_pm_late_init failed, disabling dpm\n");
			पूर्ण अन्यथा अणु
				/* set the dpm state क्रम PX since there won't be
				 * a modeset to call this.
				 */
				radeon_pm_compute_घड़ीs(rdev);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((rdev->pm.num_घातer_states > 1) &&
		    (!rdev->pm.sysfs_initialized)) अणु
			/* where's the best place to put these? */
			ret = device_create_file(rdev->dev, &dev_attr_घातer_profile);
			अगर (ret)
				DRM_ERROR("failed to create device file for power profile\n");
			ret = device_create_file(rdev->dev, &dev_attr_घातer_method);
			अगर (ret)
				DRM_ERROR("failed to create device file for power method\n");
			अगर (!ret)
				rdev->pm.sysfs_initialized = true;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम radeon_pm_fini_old(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.num_घातer_states > 1) अणु
		mutex_lock(&rdev->pm.mutex);
		अगर (rdev->pm.pm_method == PM_METHOD_PROखाता) अणु
			rdev->pm.profile = PM_PROखाता_DEFAULT;
			radeon_pm_update_profile(rdev);
			radeon_pm_set_घड़ीs(rdev);
		पूर्ण अन्यथा अगर (rdev->pm.pm_method == PM_METHOD_DYNPM) अणु
			/* reset शेष घड़ीs */
			rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
			rdev->pm.dynpm_planned_action = DYNPM_ACTION_DEFAULT;
			radeon_pm_set_घड़ीs(rdev);
		पूर्ण
		mutex_unlock(&rdev->pm.mutex);

		cancel_delayed_work_sync(&rdev->pm.dynpm_idle_work);

		device_हटाओ_file(rdev->dev, &dev_attr_घातer_profile);
		device_हटाओ_file(rdev->dev, &dev_attr_घातer_method);
	पूर्ण

	radeon_hwmon_fini(rdev);
	kमुक्त(rdev->pm.घातer_state);
पूर्ण

अटल व्योम radeon_pm_fini_dpm(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.num_घातer_states > 1) अणु
		mutex_lock(&rdev->pm.mutex);
		radeon_dpm_disable(rdev);
		mutex_unlock(&rdev->pm.mutex);

		device_हटाओ_file(rdev->dev, &dev_attr_घातer_dpm_state);
		device_हटाओ_file(rdev->dev, &dev_attr_घातer_dpm_क्रमce_perक्रमmance_level);
		/* XXX backwards compat */
		device_हटाओ_file(rdev->dev, &dev_attr_घातer_profile);
		device_हटाओ_file(rdev->dev, &dev_attr_घातer_method);
	पूर्ण
	radeon_dpm_fini(rdev);

	radeon_hwmon_fini(rdev);
	kमुक्त(rdev->pm.घातer_state);
पूर्ण

व्योम radeon_pm_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_fini_dpm(rdev);
	अन्यथा
		radeon_pm_fini_old(rdev);
पूर्ण

अटल व्योम radeon_pm_compute_घड़ीs_old(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;

	अगर (rdev->pm.num_घातer_states < 2)
		वापस;

	mutex_lock(&rdev->pm.mutex);

	rdev->pm.active_crtcs = 0;
	rdev->pm.active_crtc_count = 0;
	अगर (rdev->num_crtc && rdev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc,
				    &ddev->mode_config.crtc_list, head) अणु
			radeon_crtc = to_radeon_crtc(crtc);
			अगर (radeon_crtc->enabled) अणु
				rdev->pm.active_crtcs |= (1 << radeon_crtc->crtc_id);
				rdev->pm.active_crtc_count++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rdev->pm.pm_method == PM_METHOD_PROखाता) अणु
		radeon_pm_update_profile(rdev);
		radeon_pm_set_घड़ीs(rdev);
	पूर्ण अन्यथा अगर (rdev->pm.pm_method == PM_METHOD_DYNPM) अणु
		अगर (rdev->pm.dynpm_state != DYNPM_STATE_DISABLED) अणु
			अगर (rdev->pm.active_crtc_count > 1) अणु
				अगर (rdev->pm.dynpm_state == DYNPM_STATE_ACTIVE) अणु
					cancel_delayed_work(&rdev->pm.dynpm_idle_work);

					rdev->pm.dynpm_state = DYNPM_STATE_PAUSED;
					rdev->pm.dynpm_planned_action = DYNPM_ACTION_DEFAULT;
					radeon_pm_get_dynpm_state(rdev);
					radeon_pm_set_घड़ीs(rdev);

					DRM_DEBUG_DRIVER("radeon: dynamic power management deactivated\n");
				पूर्ण
			पूर्ण अन्यथा अगर (rdev->pm.active_crtc_count == 1) अणु
				/* TODO: Increase घड़ीs अगर needed क्रम current mode */

				अगर (rdev->pm.dynpm_state == DYNPM_STATE_MINIMUM) अणु
					rdev->pm.dynpm_state = DYNPM_STATE_ACTIVE;
					rdev->pm.dynpm_planned_action = DYNPM_ACTION_UPCLOCK;
					radeon_pm_get_dynpm_state(rdev);
					radeon_pm_set_घड़ीs(rdev);

					schedule_delayed_work(&rdev->pm.dynpm_idle_work,
							      msecs_to_jअगरfies(RADEON_IDLE_LOOP_MS));
				पूर्ण अन्यथा अगर (rdev->pm.dynpm_state == DYNPM_STATE_PAUSED) अणु
					rdev->pm.dynpm_state = DYNPM_STATE_ACTIVE;
					schedule_delayed_work(&rdev->pm.dynpm_idle_work,
							      msecs_to_jअगरfies(RADEON_IDLE_LOOP_MS));
					DRM_DEBUG_DRIVER("radeon: dynamic power management activated\n");
				पूर्ण
			पूर्ण अन्यथा अणु /* count == 0 */
				अगर (rdev->pm.dynpm_state != DYNPM_STATE_MINIMUM) अणु
					cancel_delayed_work(&rdev->pm.dynpm_idle_work);

					rdev->pm.dynpm_state = DYNPM_STATE_MINIMUM;
					rdev->pm.dynpm_planned_action = DYNPM_ACTION_MINIMUM;
					radeon_pm_get_dynpm_state(rdev);
					radeon_pm_set_घड़ीs(rdev);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&rdev->pm.mutex);
पूर्ण

अटल व्योम radeon_pm_compute_घड़ीs_dpm(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *ddev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	काष्ठा radeon_connector *radeon_connector;

	अगर (!rdev->pm.dpm_enabled)
		वापस;

	mutex_lock(&rdev->pm.mutex);

	/* update active crtc counts */
	rdev->pm.dpm.new_active_crtcs = 0;
	rdev->pm.dpm.new_active_crtc_count = 0;
	rdev->pm.dpm.high_pixelघड़ी_count = 0;
	अगर (rdev->num_crtc && rdev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc,
				    &ddev->mode_config.crtc_list, head) अणु
			radeon_crtc = to_radeon_crtc(crtc);
			अगर (crtc->enabled) अणु
				rdev->pm.dpm.new_active_crtcs |= (1 << radeon_crtc->crtc_id);
				rdev->pm.dpm.new_active_crtc_count++;
				अगर (!radeon_crtc->connector)
					जारी;

				radeon_connector = to_radeon_connector(radeon_crtc->connector);
				अगर (radeon_connector->pixelघड़ी_क्रम_modeset > 297000)
					rdev->pm.dpm.high_pixelघड़ी_count++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* update battery/ac status */
	अगर (घातer_supply_is_प्रणाली_supplied() > 0)
		rdev->pm.dpm.ac_घातer = true;
	अन्यथा
		rdev->pm.dpm.ac_घातer = false;

	radeon_dpm_change_घातer_state_locked(rdev);

	mutex_unlock(&rdev->pm.mutex);

पूर्ण

व्योम radeon_pm_compute_घड़ीs(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->pm.pm_method == PM_METHOD_DPM)
		radeon_pm_compute_घड़ीs_dpm(rdev);
	अन्यथा
		radeon_pm_compute_घड़ीs_old(rdev);
पूर्ण

अटल bool radeon_pm_in_vbl(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक  crtc, vpos, hpos, vbl_status;
	bool in_vbl = true;

	/* Iterate over all active crtc's. All crtc's must be in vblank,
	 * otherwise वापस in_vbl == false.
	 */
	क्रम (crtc = 0; (crtc < rdev->num_crtc) && in_vbl; crtc++) अणु
		अगर (rdev->pm.active_crtcs & (1 << crtc)) अणु
			vbl_status = radeon_get_crtc_scanoutpos(rdev->ddev,
								crtc,
								USE_REAL_VBLANKSTART,
								&vpos, &hpos, शून्य, शून्य,
								&rdev->mode_info.crtcs[crtc]->base.hwmode);
			अगर ((vbl_status & DRM_SCANOUTPOS_VALID) &&
			    !(vbl_status & DRM_SCANOUTPOS_IN_VBLANK))
				in_vbl = false;
		पूर्ण
	पूर्ण

	वापस in_vbl;
पूर्ण

अटल bool radeon_pm_debug_check_in_vbl(काष्ठा radeon_device *rdev, bool finish)
अणु
	u32 stat_crtc = 0;
	bool in_vbl = radeon_pm_in_vbl(rdev);

	अगर (!in_vbl)
		DRM_DEBUG_DRIVER("not in vbl for pm change %08x at %s\n", stat_crtc,
			 finish ? "exit" : "entry");
	वापस in_vbl;
पूर्ण

अटल व्योम radeon_dynpm_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_device *rdev;
	पूर्णांक resched;
	rdev = container_of(work, काष्ठा radeon_device,
				pm.dynpm_idle_work.work);

	resched = tपंचांग_bo_lock_delayed_workqueue(&rdev->mman.bdev);
	mutex_lock(&rdev->pm.mutex);
	अगर (rdev->pm.dynpm_state == DYNPM_STATE_ACTIVE) अणु
		पूर्णांक not_processed = 0;
		पूर्णांक i;

		क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
			काष्ठा radeon_ring *ring = &rdev->ring[i];

			अगर (ring->पढ़ोy) अणु
				not_processed += radeon_fence_count_emitted(rdev, i);
				अगर (not_processed >= 3)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (not_processed >= 3) अणु /* should upघड़ी */
			अगर (rdev->pm.dynpm_planned_action == DYNPM_ACTION_DOWNCLOCK) अणु
				rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
			पूर्ण अन्यथा अगर (rdev->pm.dynpm_planned_action == DYNPM_ACTION_NONE &&
				   rdev->pm.dynpm_can_upघड़ी) अणु
				rdev->pm.dynpm_planned_action =
					DYNPM_ACTION_UPCLOCK;
				rdev->pm.dynpm_action_समयout = jअगरfies +
				msecs_to_jअगरfies(RADEON_RECLOCK_DELAY_MS);
			पूर्ण
		पूर्ण अन्यथा अगर (not_processed == 0) अणु /* should करोwnघड़ी */
			अगर (rdev->pm.dynpm_planned_action == DYNPM_ACTION_UPCLOCK) अणु
				rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
			पूर्ण अन्यथा अगर (rdev->pm.dynpm_planned_action == DYNPM_ACTION_NONE &&
				   rdev->pm.dynpm_can_करोwnघड़ी) अणु
				rdev->pm.dynpm_planned_action =
					DYNPM_ACTION_DOWNCLOCK;
				rdev->pm.dynpm_action_समयout = jअगरfies +
				msecs_to_jअगरfies(RADEON_RECLOCK_DELAY_MS);
			पूर्ण
		पूर्ण

		/* Note, radeon_pm_set_घड़ीs is called with अटल_चयन set
		 * to false since we want to रुको क्रम vbl to aव्योम flicker.
		 */
		अगर (rdev->pm.dynpm_planned_action != DYNPM_ACTION_NONE &&
		    jअगरfies > rdev->pm.dynpm_action_समयout) अणु
			radeon_pm_get_dynpm_state(rdev);
			radeon_pm_set_घड़ीs(rdev);
		पूर्ण

		schedule_delayed_work(&rdev->pm.dynpm_idle_work,
				      msecs_to_jअगरfies(RADEON_IDLE_LOOP_MS));
	पूर्ण
	mutex_unlock(&rdev->pm.mutex);
	tपंचांग_bo_unlock_delayed_workqueue(&rdev->mman.bdev, resched);
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक radeon_debugfs_pm_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	काष्ठा drm_device *ddev = rdev->ddev;

	अगर  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->चयन_घातer_state != DRM_SWITCH_POWER_ON)) अणु
		seq_म_लिखो(m, "PX asic powered off\n");
	पूर्ण अन्यथा अगर (rdev->pm.dpm_enabled) अणु
		mutex_lock(&rdev->pm.mutex);
		अगर (rdev->asic->dpm.debugfs_prपूर्णांक_current_perक्रमmance_level)
			radeon_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(rdev, m);
		अन्यथा
			seq_म_लिखो(m, "Debugfs support not implemented for this asic\n");
		mutex_unlock(&rdev->pm.mutex);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "default engine clock: %u0 kHz\n", rdev->pm.शेष_sclk);
		/* radeon_get_engine_घड़ी is not reliable on APUs so just prपूर्णांक the current घड़ी */
		अगर ((rdev->family >= CHIP_PALM) && (rdev->flags & RADEON_IS_IGP))
			seq_म_लिखो(m, "current engine clock: %u0 kHz\n", rdev->pm.current_sclk);
		अन्यथा
			seq_म_लिखो(m, "current engine clock: %u0 kHz\n", radeon_get_engine_घड़ी(rdev));
		seq_म_लिखो(m, "default memory clock: %u0 kHz\n", rdev->pm.शेष_mclk);
		अगर (rdev->asic->pm.get_memory_घड़ी)
			seq_म_लिखो(m, "current memory clock: %u0 kHz\n", radeon_get_memory_घड़ी(rdev));
		अगर (rdev->pm.current_vddc)
			seq_म_लिखो(m, "voltage: %u mV\n", rdev->pm.current_vddc);
		अगर (rdev->asic->pm.get_pcie_lanes)
			seq_म_लिखो(m, "PCIE lanes: %d\n", radeon_get_pcie_lanes(rdev));
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(radeon_debugfs_pm_info);
#पूर्ण_अगर

अटल व्योम radeon_debugfs_pm_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("radeon_pm_info", 0444, root, rdev,
			    &radeon_debugfs_pm_info_fops);

#पूर्ण_अगर
पूर्ण
