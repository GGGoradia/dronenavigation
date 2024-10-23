function visualizePath(file, titleStr)
    % Read the CSV file
    path = csvread(file);

    % Plot the path
    plot(path(:,2), path(:,1), 'bo-', 'LineWidth', 2, 'MarkerFaceColor', 'b');
    axis equal;
    grid on;
    title(titleStr);

    % Save the figure as an image
    saveas(gcf, [titleStr, '.png']);
end

% Visualize both paths
figure;
visualizePath('../output/a_star_path.csv', 'A* Algorithm Path');

figure;
visualizePath('../output/bellman_ford_path.csv', 'Bellman-Ford Algorithm Path');
