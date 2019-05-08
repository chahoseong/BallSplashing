#include "credit.h"
#include "type.h"
#include "game.h"
#include "renderer.h"

#include <stdlib.h>
#include <string.h>

typedef struct TextNode
{
	wchar_t* text;
	Vector2 position;
	struct TextNode* next;
} TextNode;

typedef struct Credit
{
	TextNode* head;
	float scroll_speed;
} Credit;

Credit* CreateCredit(Renderer* renderer, const char* filename)
{
	Credit* credit = (Credit*)malloc(sizeof(Credit));
	if (!credit)
		return NULL;

	FILE* fp = NULL;
	fopen_s(&fp, filename, "r");

	if (!fp)
		return NULL;

	credit->head = (TextNode*)malloc(sizeof(TextNode));
	if (!credit->head)
		return NULL;

	memset(credit->head, 0, sizeof(TextNode));
	
	int width = 0, height = 0;
	GetRenderSize(renderer, &width, &height);

	TextNode* last = NULL;
	char buffer[_MAX_PATH];

	while (fgets(buffer, _MAX_PATH, fp))
	{
		TextNode* node = (TextNode*)malloc(sizeof(TextNode));
		node->position.x = width / 2;
		node->position.y = height++;

		int size = strlen(buffer) + 1;
		node->text = (wchar_t*)malloc(sizeof(wchar_t) * size);
		mbstowcs_s(NULL, node->text, size, buffer, size);

		if (!last)
		{
			credit->head->next = node;
			last = node;
		}
		else
		{
			node->next = NULL;
			last->next = node;
			last = node;
		}
	}

	return credit;
}

void DestroyCredit(Credit* credit)
{
	TextNode* node = credit->head->next;
	while (node != NULL)
	{
		TextNode* del = node;
		node = node->next;
		
		free(del->text);
		free(del);
	}

	free(credit->head);
	free(credit);
}

void UpdateCredit(Credit* credit, float delta_time)
{
	static float timer = 0.0f;

	timer += delta_time;

	if (timer > 0.35f)
	{
		TextNode* node = credit->head->next;
		while (node != NULL)
		{
			--node->position.y;
			node = node->next;
		}

		timer = 0.0f;
	}
}

void RenderCredit(Renderer* renderer, Credit* credit)
{
	TextNode* node = credit->head->next;
	
	int width = 0, height = 0;
	GetRenderSize(renderer, &width, &height);

	while (node != NULL)
	{
		if (node->position.y >= 0 && node->position.y < height)
		{
			SetRenderDrawColor(renderer, WHITE, BLACK);
			RenderDrawText(renderer, node->text, wcslen(node->text), node->position.x, node->position.y, ALIGN_CENTER);
		}

		node = node->next;
	}
}