/* SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "cJSON.h"

/*<! Enum for image sizes */
typedef enum {
    OPENAI_IMAGE_SIZE_1024x1024,
    OPENAI_IMAGE_SIZE_512x512,
    OPENAI_IMAGE_SIZE_256x256
} OpenAI_Image_Size;

/*<! Enum for image response formats */
typedef enum {
    OPENAI_IMAGE_RESPONSE_FORMAT_URL,
    OPENAI_IMAGE_RESPONSE_FORMAT_B64_JSON
} OpenAI_Image_Response_Format;

/*<! Enum for audio response formats */
typedef enum {
    OPENAI_AUDIO_RESPONSE_FORMAT_JSON,
    OPENAI_AUDIO_RESPONSE_FORMAT_TEXT,
    OPENAI_AUDIO_RESPONSE_FORMAT_SRT,
    OPENAI_AUDIO_RESPONSE_FORMAT_VERBOSE_JSON,
    OPENAI_AUDIO_RESPONSE_FORMAT_VTT
} OpenAI_Audio_Response_Format;

/*<! Enum for audio input formats */
typedef enum {
    OPENAI_AUDIO_INPUT_FORMAT_MP3,
    OPENAI_AUDIO_INPUT_FORMAT_MP4,
    OPENAI_AUDIO_INPUT_FORMAT_MPEG,
    OPENAI_AUDIO_INPUT_FORMAT_MPGA,
    OPENAI_AUDIO_INPUT_FORMAT_M4A,
    OPENAI_AUDIO_INPUT_FORMAT_WAV,
    OPENAI_AUDIO_INPUT_FORMAT_WEBM
} OpenAI_Audio_Input_Format;

/**
 * @brief Struct for Embedding data
 * 
 */
typedef struct {
    uint32_t len;  /*!< Length of the data */
    double *data;  /*!< Pointer to the data */
} OpenAI_EmbeddingData_t;

/**
 * @brief To get an embedding, send your text string to the embeddings API
 *        endpoint along with a choice of embedding model ID (e.g., text-embedding-ada-002).
 *        The response will contain an embedding, which you can extract, save, and use.
 */
typedef struct OpenAI_EmbeddingResponse {

    /**
     * @brief Get the usage of OpenAI_EmbeddingResponse
     *
     * @param stringResponse[in] The pointer to OpenAI_EmbeddingResponse
     * @return uint32_t
     */
    uint32_t (*getUsage)(struct OpenAI_EmbeddingResponse *stringResponse);

    /**
     * @brief Get the length of OpenAI_EmbeddingResponse
     *
     * @param embeddingData[in] The pointer to OpenAI_EmbeddingResponse
     * @return uint32_t
     */
    uint32_t (*getLen)(struct OpenAI_EmbeddingResponse *embeddingData);

    /**
     * @brief Get the data of OpenAI_EmbeddingResponse
     *
     * @param embeddingData[in] The pointer to OpenAI_EmbeddingResponse
     * @param index[in] The index of the data
     * @return OpenAI_EmbeddingData_t*
     */
    OpenAI_EmbeddingData_t *(*getData)(struct OpenAI_EmbeddingResponse *embeddingData, uint32_t index);

    /**
     * @brief Get the error of OpenAI_EmbeddingResponse
     *
     * @param embeddingData[in] The pointer to OpenAI_EmbeddingResponse
     * @return char*
     */
    char *(*getError)(struct OpenAI_EmbeddingResponse *embeddingData);

    /**
     * @brief delete the embedding response, should free it after use.
     *
     * @param embeddingData[in] the point of OpenAI_EmbeddingResponse
     */
    void (*delete)(struct OpenAI_EmbeddingResponse *embeddingData);
} OpenAI_EmbeddingResponse_t;

/**
 * @brief The moderations endpoint is a tool you can use to check whether content complies with OpenAI's usage policies.
 *        Developers can thus identify content that our usage policies prohibits and take action, for instance by filtering it.
 */
typedef struct OpenAI_ModerationResponse {

    /**
     * @brief Get the length of OpenAI_ModerationResponse
     *
     * @param moderationResponse[in] The pointer to OpenAI_ModerationResponse
     * @return uint32_t
     */
    uint32_t (*getLen)(struct OpenAI_ModerationResponse *moderationResponse);

    /**
     * @brief Get the moderation result of OpenAI_ModerationResponse
     *
     * @param moderationResponse[in] The pointer to OpenAI_ModerationResponse
     * @param index[in] The index of the moderation result
     * @return bool
     */
    bool (*getData)(struct OpenAI_ModerationResponse *moderationResponse, uint32_t index);

    /**
     * @brief Get the error message of OpenAI_ModerationResponse
     *
     * @param moderationResponse[in] The pointer to OpenAI_ModerationResponse
     * @return char*
     */
    char *(*getError)(struct OpenAI_ModerationResponse *moderationResponse);

    /**
     * @brief delete the moderation response, should free it after use.
     *
     * @param moderationResponse[in] the point of } OpenAI_ModerationResponse_t
     */
    void (*delete)(struct OpenAI_ModerationResponse *moderationResponse);
} OpenAI_ModerationResponse_t;

/**
 * @brief Save the image which is generated by OpenAI
 *
 */
typedef struct OpenAI_ImageResponse {

    /**
     * @brief Get the length of OpenAI_ImageResponse
     *
     * @param imageResponse[in] The pointer to OpenAI_ImageResponse
     * @return uint32_t
     */
    uint32_t (*getLen)(struct OpenAI_ImageResponse *imageResponse);

    /**
     * @brief Get the data of OpenAI_ImageResponse
     *
     * @param imageResponse[in] The pointer to OpenAI_ImageResponse
     * @param index[in] The index of the image data
     * @return char*
     */
    char *(*getData)(struct OpenAI_ImageResponse *imageResponse, uint32_t index);

    /**
     * @brief Get the error message of OpenAI_ImageResponse
     *
     * @param imageResponse[in] The pointer to OpenAI_ImageResponse
     * @return char*
     */
    char *(*getError)(struct OpenAI_ImageResponse *imageResponse);

    /**
     * @brief delete the image response
     *
     * @param imageResponse[in] the point of } OpenAI_ImageResponse_t
     */
    void (*delete)(struct OpenAI_ImageResponse *imageResponse);
} OpenAI_ImageResponse_t;

/**
 * @brief Parse the returned json data into OpenAI_StringResponse_t
 */
typedef struct OpenAI_StringResponse {
    /**
     * @brief get the usage of openai response
     *
     * @param stringResponse[in] the point of OpenAI_StringResponse_t
     * @return uint32_t
     */
    uint32_t (*getUsage)(struct OpenAI_StringResponse *stringResponse);

    /**
     * @brief get the len of openai response
     *
     * @param stringResponse[in] the point of OpenAI_StringResponse_t
     * @return uint32_t
     */
    uint32_t (*getLen)(struct OpenAI_StringResponse *stringResponse);

    /**
     * @brief get the data of openai response
     *
     * @param stringResponse[in] the point of OpenAI_StringResponse_t
     * @param index[in] the index of data
     * @return char*
     */
    char *(*getData)(struct OpenAI_StringResponse *stringResponse, uint32_t index);

    /**
     * @brief get the error of openai response
     *
     * @param stringResponse[in] the point of OpenAI_StringResponse_t
     * @return char*
     */
    char *(*getError)(struct OpenAI_StringResponse *stringResponse);

    /**
     * @brief delete the openai response
     *
     * @param stringResponse[in] the point of OpenAI_StringResponse_t
     */
    void (*delete)(struct OpenAI_StringResponse *stringResponse);
} OpenAI_StringResponse_t;

/**
 * @brief Given a prompt, the model will return one or more predicted completions,
 * and can also return the probabilities of alternative tokens at each position.
 *
 */
typedef struct OpenAI_Completion {

    /**
     * @brief Set the model to use for completion
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param m[in] the name of the model to use for completion
     */
    void (*setModel)(struct OpenAI_Completion *completion, const char *m);

    /**
     * @brief Set the maximum number of tokens to generate in the completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param mt[in] the maximum number of tokens to generate in the completion
     */
    void (*setMaxTokens)(struct OpenAI_Completion *completion, uint32_t mt);

    /**
     * @brief Set the temperature of the completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param t[in] float between 0 and 2. Higher value gives more random results.
     */
    void (*setTemperature)(struct OpenAI_Completion *completion, float t);

    /**
     * @brief Set the value of top_p for the completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param tp[in] float between 0 and 1. recommended to alter this or temperature but not both.
     */
    void (*setTopP)(struct OpenAI_Completion *completion, float tp);

    /**
     * @brief Set the number of completions to generate for each prompt.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param n[in] the number of completions to generate for each prompt
     */
    void (*setN)(struct OpenAI_Completion *completion, uint32_t n);

    /**
     * @brief Echo back the prompt in addition to the completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param e[in] true if the prompt should be echoed back, false otherwise
     */
    void (*setEcho)(struct OpenAI_Completion *completion, bool e);

    /**
     * @brief Set up to 4 sequences where the API will stop generating further tokens.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param s[in] the sequences where the API will stop generating further tokens
     */
    void (*setStop)(struct OpenAI_Completion *completion, const char *s);

    /**
     * @brief Set the presence penalty for the completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param pp[in] float between -2.0 and 2.0. Positive values increase the model's likelihood to talk about new topics.
     */
    void (*setPresencePenalty)(struct OpenAI_Completion *completion, float pp);

    /**
     * @brief Set the frequency penalty for the completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param fp[in] float between -2.0 and 2.0. Positive values decrease the model's likelihood to repeat the same line verbatim.
     */
    void (*setFrequencyPenalty)(struct OpenAI_Completion *completion, float fp);

    /**
     * @brief Generates best_of completions server-side and returns the "best". "best_of" must be greater than "n".
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param bo[in] the number of best_of completions to generate server-side and return the "best"
     */
    void (*setBestOf)(struct OpenAI_Completion *completion, uint32_t bo);

    /**
     * @brief A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param u[in] the unique identifier representing your end-user
     */
    void (*setUser)(struct OpenAI_Completion *completion, const char *u);

    /**
     * @brief Send the prompt for completion.
     *
     * @param completion[in] the point of OpenAI_Completion_t
     * @param p[in] the prompt for completion
     * @return OpenAI_StringResponse_t*
     */
    OpenAI_StringResponse_t *(*prompt)(struct OpenAI_Completion *completion, char *p);
} OpenAI_Completion_t;

/**
 * @brief Given a list of messages comprising a conversation, the model will return a response.
 *
 */
typedef struct OpenAI_ChatCompletion {
    /**
     * @brief Set the model to use for completion
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param m[in] the name of the model to use for chatCompletion
     */
    void (*setModel)(struct OpenAI_ChatCompletion *chatCompletion, const char *m);

    /**
     * @brief Set the system to use for completion
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param s[in] description of the required assistant
     */
    void (*setSystem)(struct OpenAI_ChatCompletion *chatCompletion, const char *s);

    /**
     * @brief Set the maximum number of tokens to generate in the completion.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param mt[in] the maximum number of tokens to generate in the completion
     */
    void (*setMaxTokens)(struct OpenAI_ChatCompletion *chatCompletion, uint32_t mt);

    /**
     * @brief Set the temperature for the completion.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param t[in] float between 0 and 2. Higher value gives more random results.
     */
    void (*setTemperature)(struct OpenAI_ChatCompletion *chatCompletion, float t);

    /**
     * @brief Set the top_p for the completion.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param tp[in] float between 0 and 1. recommended to alter this or temperature but not both.
     */
    void (*setTopP)(struct OpenAI_ChatCompletion *chatCompletion, float tp);

    /**
     * @brief Set up to 4 sequences where the API will stop generating further tokens.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param s[in] the sequences where the API will stop generating further tokens
     */
    void (*setStop)(struct OpenAI_ChatCompletion *chatCompletion, const char *s);

    /**
     * @brief Set the presence penalty for the completion.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param pp[in] float between -2.0 and 2.0. Positive values increase the model's likelihood to talk about new topics.
     */
    void (*setPresencePenalty)(struct OpenAI_ChatCompletion *chatCompletion, float pp);

    /**
     * @brief Set the frequency penalty for the completion.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param fp[in] float between -2.0 and 2.0. Positive values decrease the model's likelihood to repeat the same line verbatim.
     */
    void (*setFrequencyPenalty)(struct OpenAI_ChatCompletion *chatCompletion, float fp);

    /**
     * @brief A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param u[in] the unique identifier representing your end-user
     */
    void (*setUser)(struct OpenAI_ChatCompletion *chatCompletion, const char *u);

    /**
     * @brief Clears the accumulated conversation.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     */
    void (*clearConversation)(struct OpenAI_ChatCompletion *chatCompletion);

    /**
     * @brief Send the message for completion. Save it with the first response if selected.
     *
     * @param chatCompletion[in] the point of OpenAI_ChatCompletion
     * @param p[in] the message for completion
     * @param save[in] save it with the first response if selected
     * @return OpenAI_StringResponse_t*
     */
    OpenAI_StringResponse_t *(*message)(struct OpenAI_ChatCompletion *chatCompletion, const char *p, bool save);
} OpenAI_ChatCompletion_t;

/**
 * @brief Given a prompt and an instruction, the model will return an edited version of the prompt.
 *
 */
typedef struct OpenAI_Edit {
    /**
     * @brief Set the model to use for edit
     *
     * @param edit[in] the point of OpenAI_Edit_t
     * @param m[in] the name of the model to use for edit
     */
    void (*setModel)(struct OpenAI_Edit *edit, const char *m);

    /**
     * @brief Set the temperature for the edit.
     *
     * @param edit[in] the point of OpenAI_Edit_t
     * @param t[in] float between 0 and 2. Higher value gives more random results.
     */
    void (*setTemperature)(struct OpenAI_Edit *edit, float t);

    /**
     * @brief Set the top_p for the edit.
     *
     * @param edit[in] the point of OpenAI_Edit_t
     * @param tp[in] float between 0 and 1. recommended to alter this or temperature but not both.
     */
    void (*setTopP)(struct OpenAI_Edit *edit, float tp);

    /**
     * @brief Set the number of edits to generate for the input and instruction.
     *
     * @param edit[in] the point of OpenAI_Edit_t
     * @param n[in] the number of edits to generate for the input and instruction
     */
    void (*setN)(struct OpenAI_Edit *edit, uint32_t n);

    /**
     * @brief Creates a new edit for the provided input, instruction, and parameters.
     *
     * @param edit[in] the point of OpenAI_Edit_t
     * @param instruction[in] the instruction for the edit
     * @param input[in] the input text to be edited
     * @return OpenAI_StringResponse_t* the edited text
     */
    OpenAI_StringResponse_t *(*process)(struct OpenAI_Edit *edit, char *instruction, char *input);
} OpenAI_Edit_t;

/**
 * @brief Creates an image given a prompt.
 *
 */
typedef struct OpenAI_ImageGeneration {
    /**
     * @brief Set the size of the generated images.
     *
     * @param imageGeneration[in] the point of OpenAI_ImageGeneration
     * @param s[in] the size of the generated images
     */
    void (*setSize)(struct OpenAI_ImageGeneration *imageGeneration, OpenAI_Image_Size s);

    /**
     * @brief Set the format in which the generated images are returned.
     *
     * @param imageGeneration[in] the point of OpenAI_ImageGeneration
     * @param rf[in] the format in which the generated images are returned
     */
    void (*setResponseFormat)(struct OpenAI_ImageGeneration *imageGeneration, OpenAI_Image_Response_Format rf);

    /**
     * @brief Set the number of images to generate. Must be between 1 and 10.
     *
     * @param imageGeneration[in] the point of OpenAI_ImageGeneration
     * @param n[in] the number of images to generate
     */
    void (*setN)(struct OpenAI_ImageGeneration *imageGeneration, uint32_t n);

    /**
     * @brief Set a unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
     *
     * @param imageGeneration[in] the point of OpenAI_ImageGeneration
     * @param u[in] the unique identifier representing your end-user
     */
    void (*setUser)(struct OpenAI_ImageGeneration *imageGeneration, const char *u);

    /**
     * @brief Creates image/images from given a prompt.
     *
     * @param imageGeneration[in] the point of OpenAI_ImageGeneration
     * @param p[in] the prompt for image generation
     * @return OpenAI_ImageResponse_t* the generated image/images
     */
    OpenAI_ImageResponse_t *(*prompt)(struct OpenAI_ImageGeneration *imageGeneration, char *p);
} OpenAI_ImageGeneration_t;

/**
 * @brief Creates a variation of a given image.
 *
 */
typedef struct OpenAI_ImageVariation {
    /**
     * @brief Set the size of the generated images.
     *
     * @param imageVariation[in] the point of OpenAI_ImageVariation
     * @param s[in] the size of the generated images
     */
    void (*setSize)(struct OpenAI_ImageVariation *imageVariation, OpenAI_Image_Size s);
    /**
     * @brief Set the format in which the generated images are returned.
     *
     * @param imageVariation[in] the point of OpenAI_ImageVariation
     * @param rf[in] the format in which the generated images are returned
     */
    void (*setResponseFormat)(struct OpenAI_ImageVariation *imageVariation, OpenAI_Image_Response_Format rf);
    /**
     * @brief Set the number of images to generate. Must be between 1 and 10.
     *
     * @param imageVariation[in] the point of OpenAI_ImageVariation
     * @param n[in] the number of images to generate
     */
    void (*setN)(struct OpenAI_ImageVariation *imageVariation, uint32_t n);
    /**
     * @brief Set a unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
     *
     * @param imageVariation[in] the point of OpenAI_ImageVariation
     * @param u[in] the unique identifier representing your end-user
     */
    void (*setUser)(struct OpenAI_ImageVariation *imageVariation, const char *u);

    /**
     * @brief Creates an image variation from given image data.
     *
     * @param imageVariation[in] the point of OpenAI_ImageVariation
     * @param data[in] the input image data
     * @param len[in] the length of the input image data
     * @return OpenAI_ImageResponse_t* the generated image variation
     */
    OpenAI_ImageResponse_t *(*image)(struct OpenAI_ImageVariation *imageVariation, uint8_t *data, size_t len);
} OpenAI_ImageVariation_t;

/**
 * @brief Creates an edited or extended image given an original image and a prompt.
 *
 */
typedef struct OpenAI_ImageEdit {
    /**
     * @brief Set the prompt for the image edit.
     *
     * @param imageEdit[in] the point of OpenAI_ImageEdit_t
     * @param p[in] the prompt for the image edit
     */
    void (*setPrompt)(struct OpenAI_ImageEdit *imageEdit, const char *p);
    /**
     * @brief Set the size of the generated images.
     *
     * @param imageEdit[in] the point of OpenAI_ImageEdit_t
     * @param s[in] the size of the generated images
     */
    void (*setSize)(struct OpenAI_ImageEdit *imageEdit, OpenAI_Image_Size s);
    /**
     * @brief Set the format in which the generated images are returned.
     *
     * @param imageEdit[in] the point of OpenAI_ImageEdit_t
     * @param rf[in] the format in which the generated images are returned
     */
    void (*setResponseFormat)(struct OpenAI_ImageEdit *imageEdit, OpenAI_Image_Response_Format rf);
    /**
     * @brief Set the number of images to generate. Must be between 1 and 10.
     *
     * @param imageEdit[in] the point of OpenAI_ImageEdit_t
     * @param n[in] the number of images to generate
     */
    void (*setN)(struct OpenAI_ImageEdit *imageEdit, uint32_t n);
    /**
     * @brief Set a unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse.
     *
     * @param imageEdit[in] the point of OpenAI_ImageEdit_t
     * @param u[in] the unique identifier representing your end-user
     */
    void (*setUser)(struct OpenAI_ImageEdit *imageEdit, const char *u);

    /**
     * @brief Creates an edited or extended image given an original image, a mask, and a prompt.
     *
     * @param imageEdit[in] the point of OpenAI_ImageEdit_t
     * @param data[in] the input image data
     * @param len[in] the length of the input image data
     * @param mask_data[in] the input mask data
     * @param mask_len[in] the length of the input mask data
     * @return OpenAI_ImageResponse_t* the edited or extended image
     */
    OpenAI_ImageResponse_t *(*image)(struct OpenAI_ImageEdit *imageEdit, uint8_t *data, size_t len, uint8_t *mask_data, size_t mask_len);
} OpenAI_ImageEdit_t;

/**
 * @brief Transcribes audio into the input language.
 *
 */
typedef struct OpenAI_AudioTranscription {

    /**
     * @brief Set the prompt for the audio transcription.
     *
     * @param audioTranscription[in] the point of OpenAI_AudioTranscription_t
     * @param p[in] the prompt for the audio transcription
     */
    void (*setPrompt)(struct OpenAI_AudioTranscription *audioTranscription, const char *p);

    /**
     * @brief Set the format of the transcript output.
     *
     * @param audioTranscription[in] the point of OpenAI_AudioTranscription_t
     * @param rf[in] the format of the transcript output
     */
    void (*setResponseFormat)(struct OpenAI_AudioTranscription *audioTranscription, OpenAI_Audio_Response_Format rf);

    /**
     * @brief Set the temperature for the audio transcription.
     *
     * @param audioTranscription[in] the point of OpenAI_AudioTranscription_t
     * @param t[in] float between 0 and 1
     */
    void (*setTemperature)(struct OpenAI_AudioTranscription *audioTranscription, float t);

    /**
     * @brief Set the language of the input audio.
     *
     * @param audioTranscription[in] the point of OpenAI_AudioTranscription_t
     * @param l[in] the language in ISO-639-1 format of the input audio. NULL for Auto.
     */
    void (*setLanguage)(struct OpenAI_AudioTranscription *audioTranscription, const char *l);

    /**
     * @brief Transcribe an audio file.
     *
     * @param audioTranscription[in] the point of OpenAI_AudioTranscription_t
     * @param data[in] the input audio data
     * @param len[in] the length of the input audio data
     * @param f[in] the format of the input audio data
     * @return char* the transcribed text, you should free it after use.
     */
    char *(*file)(struct OpenAI_AudioTranscription *audioTranscription, uint8_t *data, size_t len, OpenAI_Audio_Input_Format f);
} OpenAI_AudioTranscription_t;

/**
 * @brief Translates audio into English.
 *
 */
typedef struct OpenAI_AudioTranslation {

    /**
     * @brief Set the prompt for the audio translation.
     *
     * @param audioTranslation[in] the point of OpenAI_AudioTranslation_t
     * @param p[in] the prompt for the audio translation
     */
    void (*setPrompt)(struct OpenAI_AudioTranslation *audioTranslation, const char *p);

    /**
     * @brief Set the format of the transcript output.
     *
     * @param audioTranslation[in] the point of OpenAI_AudioTranslation_t
     * @param rf[in] the format of the transcript output
     */
    void (*setResponseFormat)(struct OpenAI_AudioTranslation *audioTranslation, OpenAI_Audio_Response_Format rf);

    /**
     * @brief Set the temperature for the audio translation.
     *
     * @param audioTranslation[in] the point of OpenAI_AudioTranslation_t
     * @param t[in] float between 0 and 2. Higher value gives more random results.
     */
    void (*setTemperature)(struct OpenAI_AudioTranslation *audioTranslation, float t);

    /**
     * @brief Transcribe and translate an audio file into English.
     *
     * @param audioTranslation[in] the point of OpenAI_AudioTranslation_t
     * @param data[in] the input audio data
     * @param len[in] the length of the input audio data
     * @param f[in] the format of the input audio data
     * @return char* the translated text in English, you should free it after use.
     */
    char *(*file)(struct OpenAI_AudioTranslation *audioTranslation, uint8_t *data, size_t len, OpenAI_Audio_Input_Format f);
} OpenAI_AudioTranslation_t;

/**
 * @brief The entry point for calling the Openai api
 *
 */
typedef struct OpenAI {
#if CONFIG_ENABLE_EMBEDDING || defined __DOXYGEN__
    /**
     * @brief Create an embedding vector representing the input text.
     *
     * @param openai[in] The OpenAI object
     * @param input[in] The input text
     * @param model[in] The model to use for creating the embedding
     * @param user[in] The unique identifier representing the end-user
     * @return OpenAI_EmbeddingResponse_t* The embedding response object
     */
    OpenAI_EmbeddingResponse_t *(*embeddingCreate)(struct OpenAI *openai, char *input, const char *model, const char *user);
#endif

#if CONFIG_ENABLE_MODERATION || defined __DOXYGEN__
    /**
     * @brief Classify if text violates OpenAI's Content Policy.
     *
     * @param openai[in] The OpenAI object
     * @param input[in] The input text
     * @param model[in] The model to use for moderation
     * @return OpenAI_ModerationResponse_t* The moderation response object
     */
    OpenAI_ModerationResponse_t *(*moderationCreate)(struct OpenAI *openai, char *input, const char *model);
#endif

#if CONFIG_ENABLE_COMPLETION || defined __DOXYGEN__
    /**
     * @brief Generate text according to the prompt.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_Completion_t* The completion object
     */
    OpenAI_Completion_t *(*completionCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created completion handle.
     *
     * @param completion[in] The completion object
     */
    void (*completionDelete)(OpenAI_Completion_t *completion);
#endif

#if CONFIG_ENABLE_CHAT_COMPLETION || defined __DOXYGEN__
    /**
     * @brief Create a chat completion object for chatting.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_ChatCompletion_t* The chat completion object
     */
    OpenAI_ChatCompletion_t *(*chatCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created chat completion handle.
     *
     * @param chatCompletion[in] The chat completion object
     */
    void (*chatDelete)(OpenAI_ChatCompletion_t *chatCompletion);
#endif

#if CONFIG_ENABLE_EDIT || defined __DOXYGEN__
    /**
     * @brief Create an edit object for editing text.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_Edit_t* The edit object
     */
    OpenAI_Edit_t *(*editCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created edit handle.
     *
     * @param edit[in] The edit object
     */
    void (*editDelete)(OpenAI_Edit_t *edit);
#endif

#if CONFIG_ENABLE_IMAGE_GENERATION || defined __DOXYGEN__
    /**
     * @brief Create an image generation object.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_ImageGeneration_t* The image generation object
     */
    OpenAI_ImageGeneration_t *(*imageGenerationCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created image generation handle.
     *
     * @param imageGeneration[in] The image generation object
     */
    void (*imageGenerationDelete)(OpenAI_ImageGeneration_t *imageGeneration);
#endif

#if CONFIG_ENABLE_IMAGE_VARIATION || defined __DOXYGEN__
    /**
     * @brief Create an image variation object.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_ImageVariation_t* The image variation object
     */
    OpenAI_ImageVariation_t *(*imageVariationCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created image variation handle.
     *
     * @param imageVariation[in] The image variation object
     */
    void (*imageVariationDelete)(OpenAI_ImageVariation_t *imageVariation);
#endif

#if CONFIG_ENABLE_IMAGE_EDIT || defined __DOXYGEN__
    /**
     * @brief Create an image editing object.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_ImageEdit_t* The image editing object
     */
    OpenAI_ImageEdit_t *(*imageEditCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created image editing handle.
     *
     * @param imageEdit[in] The image editing object
     */
    void (*imageEditDelete)(OpenAI_ImageEdit_t *imageEdit);
#endif

#if CONFIG_ENABLE_AUDIO_TRANSCRIPTION || defined __DOXYGEN__
    /**
     * @brief Create an audio transcription object.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_AudioTranscription_t* The audio transcription object
     */
    OpenAI_AudioTranscription_t *(*audioTranscriptionCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created audio transcription handle.
     *
     * @param audioTranscription[in] The audio transcription object
     */
    void (*audioTranscriptionDelete)(OpenAI_AudioTranscription_t *audioTranscription);
#endif

#if CONFIG_ENABLE_AUDIO_TRANSLATION || defined __DOXYGEN__
    /**
     * @brief Create an audio translation object.
     *
     * @param openai[in] The OpenAI object
     * @return OpenAI_AudioTranslation_t* The audio translation object
     */
    OpenAI_AudioTranslation_t *(*audioTranslationCreate)(struct OpenAI *openai);

    /**
     * @brief Delete created audio translation handle.
     *
     * @param audioTranslation[in] The audio translation object
     */
    void (*audioTranslationDelete)(OpenAI_AudioTranslation_t *audioTranslation);
#endif
} OpenAI_t;

/**
 * @brief Create an OpenAI object
 *
 * @param api_key The key of openai
 * @return OpenAI_t* The OpenAI object
 */
OpenAI_t *OpenAICreate(const char *api_key);

/**
 * @brief Clear the OpenAI object and release resources
 *
 * @param oai The OpenAI object
 */
void OpenAIDelete(OpenAI_t *oai);

/**
 * @brief Modify the Base URL of the OpenAI object
 *
 */
void OpenAIChangeBaseURL(OpenAI_t *oai, const char *baseURL);

#ifdef __cplusplus
}
#endif