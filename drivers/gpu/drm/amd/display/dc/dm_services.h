<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
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
 * Authors: AMD
 *
 */

/**
 * This file defines बाह्यal dependencies of Display Core.
 */

#अगर_अघोषित __DM_SERVICES_H__

#घोषणा __DM_SERVICES_H__

/* TODO: हटाओ when DC is complete. */
#समावेश "dm_services_types.h"
#समावेश "logger_interface.h"
#समावेश "link_service_types.h"

#अघोषित DEPRECATED

काष्ठा dmub_srv;
काष्ठा dc_dmub_srv;

irq_handler_idx dm_रेजिस्टर_पूर्णांकerrupt(
	काष्ठा dc_context *ctx,
	काष्ठा dc_पूर्णांकerrupt_params *पूर्णांक_params,
	पूर्णांकerrupt_handler ih,
	व्योम *handler_args);

/*
 *
 * GPU रेजिस्टरs access
 *
 */
uपूर्णांक32_t dm_पढ़ो_reg_func(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t address,
			  स्थिर अक्षर *func_name);

/* enable क्रम debugging new code, this adds 50k to the driver size. */
/* #घोषणा DM_CHECK_ADDR_0 */

व्योम dm_ग_लिखो_reg_func(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t address,
		       uपूर्णांक32_t value, स्थिर अक्षर *func_name);

#घोषणा dm_पढ़ो_reg(ctx, address)	\
	dm_पढ़ो_reg_func(ctx, address, __func__)

#घोषणा dm_ग_लिखो_reg(ctx, address, value)	\
	dm_ग_लिखो_reg_func(ctx, address, value, __func__)

अटल अंतरभूत uपूर्णांक32_t dm_पढ़ो_index_reg(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत cgs_ind_reg addr_space,
	uपूर्णांक32_t index)
अणु
	वापस cgs_पढ़ो_ind_रेजिस्टर(ctx->cgs_device, addr_space, index);
पूर्ण

अटल अंतरभूत व्योम dm_ग_लिखो_index_reg(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत cgs_ind_reg addr_space,
	uपूर्णांक32_t index,
	uपूर्णांक32_t value)
अणु
	cgs_ग_लिखो_ind_रेजिस्टर(ctx->cgs_device, addr_space, index, value);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_reg_field_value_ex(
	uपूर्णांक32_t reg_value,
	uपूर्णांक32_t mask,
	uपूर्णांक8_t shअगरt)
अणु
	वापस (mask & reg_value) >> shअगरt;
पूर्ण

#घोषणा get_reg_field_value(reg_value, reg_name, reg_field)\
	get_reg_field_value_ex(\
		(reg_value),\
		reg_name ## __ ## reg_field ## _MASK,\
		reg_name ## __ ## reg_field ## __SHIFT)

अटल अंतरभूत uपूर्णांक32_t set_reg_field_value_ex(
	uपूर्णांक32_t reg_value,
	uपूर्णांक32_t value,
	uपूर्णांक32_t mask,
	uपूर्णांक8_t shअगरt)
अणु
	ASSERT(mask != 0);
	वापस (reg_value & ~mask) | (mask & (value << shअगरt));
पूर्ण

#घोषणा set_reg_field_value(reg_value, value, reg_name, reg_field)\
	(reg_value) = set_reg_field_value_ex(\
		(reg_value),\
		(value),\
		reg_name ## __ ## reg_field ## _MASK,\
		reg_name ## __ ## reg_field ## __SHIFT)

uपूर्णांक32_t generic_reg_set_ex(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr, uपूर्णांक32_t reg_val, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1, ...);

uपूर्णांक32_t generic_reg_update_ex(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1, ...);

काष्ठा dc_dmub_srv *dc_dmub_srv_create(काष्ठा dc *dc, काष्ठा dmub_srv *dmub);
व्योम dc_dmub_srv_destroy(काष्ठा dc_dmub_srv **dmub_srv);

व्योम reg_sequence_start_gather(स्थिर काष्ठा dc_context *ctx);
व्योम reg_sequence_start_execute(स्थिर काष्ठा dc_context *ctx);
व्योम reg_sequence_रुको_करोne(स्थिर काष्ठा dc_context *ctx);

#घोषणा FD(reg_field)	reg_field ## __SHIFT, \
						reg_field ## _MASK

/*
 * वापस number of poll beक्रमe condition is met
 * वापस 0 अगर condition is not meet after specअगरied समय out tries
 */
व्योम generic_reg_रुको(स्थिर काष्ठा dc_context *ctx,
	uपूर्णांक32_t addr, uपूर्णांक32_t mask, uपूर्णांक32_t shअगरt, uपूर्णांक32_t condition_value,
	अचिन्हित पूर्णांक delay_between_poll_us, अचिन्हित पूर्णांक समय_out_num_tries,
	स्थिर अक्षर *func_name, पूर्णांक line);

अचिन्हित पूर्णांक snम_लिखो_count(अक्षर *pBuf, अचिन्हित पूर्णांक bufSize, अक्षर *fmt, ...);

/* These macros need to be used with soc15 रेजिस्टरs in order to retrieve
 * the actual offset.
 */
#घोषणा dm_ग_लिखो_reg_soc15(ctx, reg, inst_offset, value)	\
		dm_ग_लिखो_reg_func(ctx, reg + DCE_BASE.instance[0].segment[reg##_BASE_IDX] + inst_offset, value, __func__)

#घोषणा dm_पढ़ो_reg_soc15(ctx, reg, inst_offset)	\
		dm_पढ़ो_reg_func(ctx, reg + DCE_BASE.instance[0].segment[reg##_BASE_IDX] + inst_offset, __func__)

#घोषणा generic_reg_update_soc15(ctx, inst_offset, reg_name, n, ...)\
		generic_reg_update_ex(ctx, DCE_BASE.instance[0].segment[mm##reg_name##_BASE_IDX] +  mm##reg_name + inst_offset, \
		n, __VA_ARGS__)

#घोषणा generic_reg_set_soc15(ctx, inst_offset, reg_name, n, ...)\
		generic_reg_set_ex(ctx, DCE_BASE.instance[0].segment[mm##reg_name##_BASE_IDX] + mm##reg_name + inst_offset, 0, \
		n, __VA_ARGS__)

#घोषणा get_reg_field_value_soc15(reg_value, block, reg_num, reg_name, reg_field)\
	get_reg_field_value_ex(\
		(reg_value),\
		block ## reg_num ## _ ## reg_name ## __ ## reg_field ## _MASK,\
		block ## reg_num ## _ ## reg_name ## __ ## reg_field ## __SHIFT)

#घोषणा set_reg_field_value_soc15(reg_value, value, block, reg_num, reg_name, reg_field)\
	(reg_value) = set_reg_field_value_ex(\
		(reg_value),\
		(value),\
		block ## reg_num ## _ ## reg_name ## __ ## reg_field ## _MASK,\
		block ## reg_num ## _ ## reg_name ## __ ## reg_field ## __SHIFT)

/**************************************
 * Power Play (PP) पूर्णांकerfaces
 **************************************/

/* Gets valid घड़ीs levels from pplib
 *
 * input: clk_type - display clk / sclk / mem clk
 *
 * output: array of valid घड़ी levels क्रम given type in ascending order,
 * with invalid levels filtered out
 *
 */
bool dm_pp_get_घड़ी_levels_by_type(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
	काष्ठा dm_pp_घड़ी_levels *clk_level_info);

bool dm_pp_get_घड़ी_levels_by_type_with_latency(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
	काष्ठा dm_pp_घड़ी_levels_with_latency *clk_level_info);

bool dm_pp_get_घड़ी_levels_by_type_with_voltage(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
	काष्ठा dm_pp_घड़ी_levels_with_voltage *clk_level_info);

bool dm_pp_notअगरy_wm_घड़ी_changes(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges *wm_with_घड़ी_ranges);

व्योम dm_pp_get_funcs(काष्ठा dc_context *ctx,
		काष्ठा pp_smu_funcs *funcs);

/* DAL calls this function to notअगरy PP about completion of Mode Set.
 * For PP it means that current DCE घड़ीs are those which were वापसed
 * by dc_service_pp_pre_dce_घड़ी_change(), in the 'output' parameter.
 *
 * If the घड़ीs are higher than beक्रमe, then PP करोes nothing.
 *
 * If the घड़ीs are lower than beक्रमe, then PP reduces the voltage.
 *
 * \लeturns	true - call is successful
 *		false - call failed
 */
bool dm_pp_apply_display_requirements(
	स्थिर काष्ठा dc_context *ctx,
	स्थिर काष्ठा dm_pp_display_configuration *pp_display_cfg);

bool dm_pp_apply_घातer_level_change_request(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_घातer_level_change_request *level_change_req);

bool dm_pp_apply_घड़ी_क्रम_voltage_request(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_घड़ी_क्रम_voltage_req *घड़ी_क्रम_voltage_req);

bool dm_pp_get_अटल_घड़ीs(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_अटल_घड़ी_info *अटल_clk_info);

/****** end of PP पूर्णांकerfaces ******/

काष्ठा persistent_data_flag अणु
	bool save_per_link;
	bool save_per_edid;
पूर्ण;

bool dm_query_extended_brightness_caps
	(काष्ठा dc_context *ctx, क्रमागत dm_acpi_display_type display,
			काष्ठा dm_acpi_atअगर_backlight_caps *pCaps);

bool dm_dmcu_set_pipe(काष्ठा dc_context *ctx, अचिन्हित पूर्णांक controller_id);

/*
 *
 * prपूर्णांक-out services
 *
 */
#घोषणा dm_log_to_buffer(buffer, size, fmt, args)\
	vsnम_लिखो(buffer, size, fmt, args)

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ dm_get_बारtamp(काष्ठा dc_context *ctx)
अणु
	वापस kसमय_get_raw_ns();
पूर्ण

अचिन्हित दीर्घ दीर्घ dm_get_elapse_समय_in_ns(काष्ठा dc_context *ctx,
		अचिन्हित दीर्घ दीर्घ current_समय_stamp,
		अचिन्हित दीर्घ दीर्घ last_समय_stamp);

/*
 * perक्रमmance tracing
 */
व्योम dm_perf_trace_बारtamp(स्थिर अक्षर *func_name, अचिन्हित पूर्णांक line, काष्ठा dc_context *ctx);

#घोषणा PERF_TRACE()	dm_perf_trace_बारtamp(__func__, __LINE__, CTX)
#घोषणा PERF_TRACE_CTX(__CTX)	dm_perf_trace_बारtamp(__func__, __LINE__, __CTX)

/*
 * Debug and verअगरication hooks
 */

व्योम dm_dtn_log_begin(काष्ठा dc_context *ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx);
व्योम dm_dtn_log_append_v(काष्ठा dc_context *ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx,
	स्थिर अक्षर *msg, ...);
व्योम dm_dtn_log_end(काष्ठा dc_context *ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx);

#पूर्ण_अगर /* __DM_SERVICES_H__ */
