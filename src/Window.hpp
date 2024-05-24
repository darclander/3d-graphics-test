#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Window {

	public:
		Window() {
			SDL_Init(SDL_INIT_VIDEO);
			SDL_CreateWindowAndRenderer(1280, 720, 0, &m_window, &m_renderer);
			SDL_RenderSetScale(m_renderer, 2, 2);
		}	

		void render() {
			SDL_RenderClear(m_renderer);


			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

			for(auto &point : m_points) {
				SDL_RenderDrawPointF(m_renderer, point.x, point.y);
			}

			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);			
			SDL_RenderPresent(m_renderer);
		}

		void update() {
			// Handle input in updates
			while(SDL_PollEvent(&m_event)) {
				if(m_event.type == SDL_QUIT) {
					SDL_Quit();
					exit(0);
				}		
			}
		
		}

		void clear() {
			m_points.clear();
		}

		void pixel(float x, float y) {
			SDL_FPoint p;
			p.x = x;
			p.y = y;
			m_points.emplace_back(p);
		}

	private:
		SDL_Event m_event;
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;

		std::vector<SDL_FPoint> m_points;
};
