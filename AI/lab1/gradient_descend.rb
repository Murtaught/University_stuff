module AI_Lab1
	GRADIENT_DELTA    = 0.000001
	GRAD_DESC_STEP    = 0.2
	GRAD_DESC_EPSILON = 0.000001
	
	def self.rand_float_in(range)
		return rand * (range.max - range.min) + range.min
	end
	
	def self.gradient(f, x) # Численно вычисляет градиент ф-ии f в (.)x
		g = []
		x_copy = x.dup
		
		x_copy.each_index do |i| # для каждой координаты точки...
			x_copy[i] += GRADIENT_DELTA
			g.push( (f[*x_copy] - f[*x]) / GRADIENT_DELTA ) 
			x_copy[i] -= GRADIENT_DELTA
		end
		
		return g
	end
	
	def self.normalize(vector)
		vector.map! { |coord| coord.zero? ? 0.0 : coord.to_f / coord.abs }
	end
	
	# Метод изначально создавался способным обрабатывать функции с произвольным числом параметров 
	def self.gradient_descend(f, search_area, start_point = nil)
		# 1. выбираем начальную точку
		if start_point == nil 
			start_point = []
			search_area.each { |range| start_point.push(rand_float_in range) }
		end
		
		graph_info = [] # вектор из чисел: значение минимума на i-той итерации
		iteration_number = 0
		
		# Считаем значение функции в начальной точке
		old_value = f[*start_point]
		cur_point = start_point
		
		graph_info << old_value
		
		loop do
			iteration_number += 1
		
			# В цикле
			# Считаем градиент функции в текущей точке
			g = gradient(f, cur_point)
			
			# Нормализуем градиент (необходимость? спорный вопрос)
			#normalize(g)
			
			# Сдвигаемся по градиенту
			cur_point.size.times do |i|
				cur_point[i] -= g[i] * GRAD_DESC_STEP
			end
			
			# Считаем функцию в новой точке
			new_value = f[*cur_point]
			graph_info << new_value
			
			# Eсли изменение значения ничтожно мало - эта новая точка становится ответом
			break if (new_value - old_value).abs < GRAD_DESC_EPSILON
			
			# Иначе помечаем это значение как предыдущее и 
			# выполняем еще одну итерацию
			old_value = new_value
		end
		
		return { :answer        => cur_point, 
				 :minimum_value => f[*cur_point], 
				 :iterations    => iteration_number, 
				 :graph_info    => graph_info }
	end
end

f = -> x, y { (x - 5)**2 + (y + 1)**2 - 7 }

area = [ (-10.0..10.0), (-10.0..10.0) ]

results = AI_Lab1.gradient_descend(f, area)
p results[:answer]
p results[:minimum_value]
p results[:iterations]